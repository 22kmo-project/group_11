const db = require('../database');

const transactions = {
    getById: function (id, callback) {
        return db.query('select * from transactions where idtransactions=?', [id], callback);
    },
    getAll: function (callback) {
        return db.query('select * from transactions', callback);
    },
    add: function (transactions, callback) {
        return db.query(
            'insert into transactions (amount, bank_account_idbank_account, type, date, time) values(?,?,?,?,?)',
            [transactions.amount, transactions.bank_account_idbank_account, transactions.type,transactions.date,transactions.time],
            callback
        );
    },
    delete: function (id, callback) {
        return db.query('delete from transactions where idtransactions=?', [id], callback);
    },
    update: function (id, transactions, callback) {
        return db.query(
            'update transactions set amount=?,type=? where idtransactions=?',
            [transactions.amount, transactions.type,transactions.date,transactions.time, id],
            callback
        );
    }
};
module.exports = transactions;