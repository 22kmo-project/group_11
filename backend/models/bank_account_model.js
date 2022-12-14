const db = require('../database');

const bank_account = {
    getById: function (id, callback) {
        return db.query('select * from bank_account where idbank_account=?', [id], callback);
    },
    getAll: function (callback) {
        return db.query('select * from bank_account', callback);
    },
    add: function (bank_account, callback) {
        return db.query(
            'insert into bank_account (balance,user_iduser,credit_limit, is_credit) values(?,?,?,?)',
            [bank_account.balance, bank_account.user_iduser, bank_account.credit_limit, bank_account.is_credit],
            callback
        );
    },
    delete: function (id, callback) {
        return db.query('delete from bank_account where idbank_account=?', [id], callback);
    },
    update: function (id, bank_account, callback) {
        return db.query(
            'update bank_account set balance=?,user_iduser=?,credit_limit=?, is_credit=? where idbank_account=?',
            [bank_account.balance, bank_account.user_iduser, bank_account.credit_limit, bank_account.is_credit, id],
            callback
        );
    }
   
};
module.exports = bank_account;