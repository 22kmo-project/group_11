const express = require('express');
const router = express.Router();
const bankcard = require('../models/bankcard_model');

router.get('/',
    function (request, response) {
        bankcard.getAll(function (err, dbResult) {
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
        bankcard.getById(request.params.id, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult);
            }
        })
    });


router.post('/',
    function (request, response) {
        bankcard.add(request.body, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(request.body);
            }
        });
    });


router.delete('/:id',
    function (request, response) {
        bankcard.delete(request.params.id, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult);
            }
        });
    });


router.put('/:id',
    function (request, response) {
        bankcard.update(request.params.id, request.body, function (err, dbResult) {
            if (err) {
                response.json(err);
            } else {
                response.json(dbResult);
            }
        });
    });

module.exports = router;