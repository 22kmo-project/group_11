const express = require('express');
const router = express.Router();
const bankops = require('../models/bank_operations_model');
const bankaccount = require('../models/bank_account_model');
const transactions = require('../models/transactions_model');

router.get('/cardinfo/:card_number?',
    function (request, response) {
        bankops.getCardInfo(request.params.card_number, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                var result = {};
                // Get debit and credit accounts
                dbResult.forEach(row => {
                    console.log(row);
                    if(row.is_credit && row.type.toLowerCase()=="credit"){
                        result.credit = row;
                    }else if(!row.is_credit){
                        result.debit = row;
                    }
                });
                response.json(result);
            }
        })
    });

router.get('/history/:id?',
    function (request, response) {
        transactions.getByBankAccountId(request.params.id, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult);
            }
        })
    });


router.post('/deposit/:id?',
    function (request, response) {

        // Check if amount is valid number
        if(isNaN(request.body.amount)){
            response.send("Not valid amount");
            return;
        }

        // Get bank account info
        bankaccount.getById(request.params.id, function (err, dbResultGetAccount) {
            if (err) {
                response.json(err);
            } else {
                var accountInfo = dbResultGetAccount[0];

                // Do not deposit on credit account
                if(accountInfo.is_credit){
                    response.send("Deposit is not possible for credit account");
                    return;
                } 

                // Set new balance and update bank account
                accountInfo.balance += Number(request.body.amount);
                bankaccount.update(request.params.id, accountInfo, function (err, dbResultUpdateAccount){
                    if (err) {
                        response.json(err);
                    } else {

                        // Create transaction
                        transactions.add({amount:request.body.amount,
                            bank_account_idbank_account:request.params.id,
                            type:"deposit"}, function (err, dbResultAddTransaction){

                                // Return responses from both actions
                                if (err) {
                                    response.json({updateBankAccountResponse:dbResultUpdateAccount, addTransactionResponse:err});
                                } else {
                                    response.json({updateBankAccountResponse:dbResultUpdateAccount, addTransactionResponse:dbResultAddTransaction});
                                }
                            });
                    }
                });
                 
            }
        }); 
    });


router.post('/withdraw/:id?',
    function (request, response) {

        // Check if amount is valid number
        if(isNaN(request.body.amount)){
            response.send("Not valid amount");
            return;
        }

        // Get bank account info
        bankaccount.getById(request.params.id, function (err, dbResultGetAccount) {
            if (err) {
                response.json(err);
            } else {
                var accountInfo = dbResultGetAccount[0];

                // Return error if bank account has not enough balance or credit limit
                if(!accountInfo.is_credit && accountInfo.balance < request.body.amount){
                    response.send("Not enough balance");
                }else if(accountInfo.is_credit && accountInfo.credit_limit < request.body.amount){
                    response.send("Not enough credit limit");
                }else{

                    // Set new balance or credit limit and update bank account
                    if(accountInfo.is_credit){
                        accountInfo.credit_limit -= request.body.amount;
                    }else if(!accountInfo.is_credit){
                        accountInfo.balance -= request.body.amount;
                    }
                    bankaccount.update(request.params.id, accountInfo, function (err, dbResultUpdateAccount){
                        if (err) {
                            response.json(err);
                        } else {

                            // Create transaction
                            transactions.add({amount:request.body.amount,
                                bank_account_idbank_account:request.params.id,
                                type:"withdraw"}, function (err, dbResultAddTransaction){

                                    // Return responses from both actions
                                    if (err) {
                                        response.json({updateBankAccountResponse:dbResultUpdateAccount, addTransactionResponse:err});
                                    } else {
                                        response.json({updateBankAccountResponse:dbResultUpdateAccount, addTransactionResponse:dbResultAddTransaction});
                                    }
                                });
                        }
                    });
                }   
            }
        });       
             
    });



module.exports = router;