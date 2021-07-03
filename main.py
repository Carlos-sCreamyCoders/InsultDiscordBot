#official repo
#   https://github.com/Rapptz/discord.py

#documentation
#   https://discordpy.readthedocs.io/en/latest/
import discord
from discord.ext import commands
import sys, string, os

#what you need to type before the command in the discord server
client = commands.Bot(command_prefix = '!')


@client.event
async def on_ready():
    #only prints to console, not discord
    print('insult is ready')

@client.command()
async def helpInsult(ctx):
    await ctx.send("Commands I can run:\n!genInsult")

#the insulting part==============================
filename = "out.insult"

@client.command()
async def genInsult(ctx):
    os.system("./a.out")
    f = open(filename)
    await ctx.send(f.read())
    f.close()

#the ID is sensative, so remove it when publicating
client.run('')
