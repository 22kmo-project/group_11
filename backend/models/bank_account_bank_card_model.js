const db = require('../database');

const bank_account_bank_card = {
    getById: function (id, callback) {
        return db.query('select * from bank_account_bank_card where idbank_account_bank_card=?', [id], callback);
    },
    getAll: function (callback) {
        return db.query('select * from bank_account_bank_card', callback);
    },
    add: function (bank_account_bank_card, callback) {
        return db.query(
            'insert into bank_account_bank_card (bank_account_idbank_account,bank_card_idbank_card) values(?,?)',
            [bank_account_bank_card.bank_account_idbank_account, bank_account_bank_card.bank_card_idbank_card],
            callback
        );
    },
    delete: function (id, callback) {
        return db.query('delete from bank_account_bank_card where idbank_account_bank_card=?', [id], callback);
    },
    update: function (id, bank_account_bank_card, callback) {
        return db.query(
            'update bank_account_bank_card set bank_account_idbank_account=?,bank_card_idbank_card=? where idbank_account_bank_card=?',
            [bank_account_bank_card.bank_account_idbank_account, bank_account_bank_card.bank_card_idbank_card, id],
            callback
        );
    }
};
module.exports = bank_account_bank_card;