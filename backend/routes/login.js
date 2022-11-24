const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const bankcard = require('../models/bankcard_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.post('/', 
  function(request, response) {
    if(request.body.card_number && request.body.pin_code){
      const card = request.body.card_number;
      const pin = request.body.pin_code;
        bankcard.checkPassword(card, function(dbError, dbResult) {
          if(dbError){
            response.json(dbError.errno);
          }
          else{
            if (dbResult.length > 0) {
              bcrypt.compare(pin,dbResult[0].pin_code, function(err,compareResult) {
                if(compareResult) {
                  console.log("succes");
                  const token = generateAccessToken({ username: card });
                  response.send(token);
                }
                else {
                    console.log("wrong pin code");
                    response.send(false);
                }			
              }
              );
            }
            else{
              console.log("bankcard does not exists");
              response.send(false);
            }
          }
          }
        );
      }
    else{
      console.log("bankcard number or pin code missing");
      response.send(false);
    }
  }
);

function generateAccessToken(username) {
    dotenv.config();
    return jwt.sign(username, process.env.MY_TOKEN, { expiresIn: '1800s' });
  }
  

module.exports=router;