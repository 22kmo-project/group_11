const db = require('../database');


const bcrypt = require('bcryptjs');
const saltRounds=10;


const bankcard = {
    getById: function (id, callback) {
        return db.query('select * from bank_card where idbank_card=?', [id], callback);
    },
    getAll: function (callback) {
        return db.query('select * from bank_card', callback);
    },
    add: function (bankcard, callback) {
        bcrypt.hash(bankcard.pin_code, saltRounds, function(err, hashedPincode){
        return db.query(
            'insert into bank_card (card_number,pin_code,user_iduser,type) values(?,?,?,?)',
            [bankcard.card_number, hashedPincode, bankcard.user_iduser, bankcard.type],
            callback
        );
        });
    },
    delete: function (id, callback) {
        return db.query('delete from bank_card where idbank_card=?', [id], callback);
    },
    update: function (id, bankcard, callback) {
        bcrypt.hash(bankcard.pin_code, saltRounds, function(err, hashedPincode){
        return db.query(
            'update bank_card set pin_code=? where idbank_card=?',
            [hashedPincode, id],
            callback
        );
        });
    },
    checkPassword: function(card, callback){
        return db.query('select pin_code from bank_card where card_number=?',[card],callback);
      },
};
module.exports = bankcard;