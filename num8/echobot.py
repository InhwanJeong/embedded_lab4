#-*- coding: utf-8 -*-
from __future__ import unicode_literals
import telegram

token = "1001586011:AAE_XpdzHbWWQx7XEReFyGtpn4DBhBjkzco"
bot = telegram.Bot(token=token)
last_update_id = None

try: last_update_id = bot.getUpdates()[-1].update_id
except IndexError:
    last_update_id = None
while True:
    for update in bot.getUpdates(offset=last_update_id, timeout=10):
        chat_id = update.message.chat_id
        message = update.message.text.encode('utf-8')
        if message == b'hello':
            bot.sendMessage(chat_id=chat_id, text='world')
            last_update_id = update.update_id + 1
