const express = require('express');
const router = express.Router();
const bank_account = require('../models/bank_account_model');

router.get('/',
    function (request, response) {
        bank_account.getAll(function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                console.log(dbResult);
                response.json(dbResult);
            }
        })
    });

router.get('/:id?',
    function (request, response) {
        bank_account.getById(request.params.id, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult);
            }
        })
    });


router.post('/',
    function (request, response) {
        bank_account.add(request.body, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(request.body);
            }
        });
    });


router.delete('/:id',
    function (request, response) {
        bank_account.delete(request.params.id, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult);
            }
        });
    });


router.put('/:id',
    function (request, response) {
        bank_account.update(request.params.id, request.body, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult);
            }
        });
    });

    router.post('/nosto',
    function (request, response) {
        bank_account.nosto(request.body, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(request.body);
            }
        });
    });

module.exports = router;