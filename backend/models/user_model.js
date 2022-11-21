const db = require('../database');

const user = {
    getById: function (id, callback) {
        return db.query('select * from user where iduser=?', [id], callback);
    },
    getAll: function (callback) {
        return db.query('select * from user', callback);
    },
    add: function (user, callback) {
        return db.query(
            'insert into user (first_name,last_name,address,email,phone_number) values(?,?,?,?,?)',
            [user.first_name, user.last_name, user.address, user.email, user.phone_number],
            callback
        );
    },
    delete: function (id, callback) {
        return db.query('delete from user where iduser=?', [id], callback);
    },
    update: function (id, user, callback) {
        return db.query(
            'update user set first_name=?,last_name=?,address=?,email=?,phone_number=? where iduser=?',
            [user.first_name, user.last_name, user.address, user.email, user.phone_number, id],
            callback
        );
    }
};
module.exports = user;