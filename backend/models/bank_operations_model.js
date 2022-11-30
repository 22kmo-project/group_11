const db = require('../database');

const bankops = {
    getCardInfo: function (card_number, callback) {
        return db.query('select idbank_account, card_number, type, balance, credit_limit, is_credit from bank_card ' 
            + 'inner join bank_account_bank_card on bank_card.idbank_card = bank_account_bank_card.bank_card_idbank_card '
            + 'inner join bank_account on bank_account_bank_card.bank_account_idbank_account = bank_account.idbank_account '
            + 'where card_number = ?;',
            [card_number],
            callback);
    },
};
module.exports = bankops;