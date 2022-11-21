const mysql = require('mysql');
const connection = mysql.createPool({
    host: 'localhost',
    user: 'restuser',
    password: 'restuserpassword',
    database: 'banksimu'
});
module.exports = connection;