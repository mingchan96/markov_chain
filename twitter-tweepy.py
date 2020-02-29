import tweepy
import re 
import sys
import os
  
def erase_links(tweet): 
    tweet_temp = tweet.replace("\r"," ")
    tweet_temp = tweet_temp.replace("\n"," ")
    urls = re.findall('http[s]?://(?:[a-zA-Z]|[0-9]|[$-_@.&+]|[!*\(\), ]|(?:%[0-9a-fA-F][0-9a-fA-F]))+', tweet)
    
    for url in urls:
        tweet_temp = tweet_temp.replace(url,"")
    return tweet_temp

#Authenticate to Twitter
CONSUMER_KEY = "IFdG9FWasHOq7sYLjBI8ll6Po"
CONSUMER_SECRET = "woWfDa9IJWy5Mk3CRxNzC8xrXBDl4jSvXMzrlvoH5GR49wGsQ2"
ACCESS_TOKEN = "1055284867360022533-VLVtTmCKZudgohk5LldJx0qqC0HPre"
ACCESS_TOKEN_SECRET = "b0z3bKnyQFWT9uNw9MSQVkSY1ZoEfCwJffEgWf4cObrdH"

auth = tweepy.OAuthHandler(CONSUMER_KEY, CONSUMER_SECRET)
auth.set_access_token(ACCESS_TOKEN,ACCESS_TOKEN_SECRET)

api = tweepy.API(auth)

try:
    api.verify_credentials()
    print("App Authenticated")
except:
    sys.exit("Authentication Error")

#first argument is a tweeter screen name
#second argument is the number of quotes
#third argument is turning on the safe words

screen_name = sys.argv[1]
# screen_name = "ellonmusk"
timeline = None
try:
    print("Retrieving tweets: " + screen_name)
    timeline = api.user_timeline(screen_name = screen_name, count=200, include_rts=False,tweet_mode="extended")
    # print(timeline)
except:
    sys.exit("Sorry error in querying the screen name")

#open file to write the tweets in 
output_file = open(screen_name+".txt", "w")
for tweet in timeline:
    # print(tweet.full_text)
    # processed_tweet = erase_links(tweet.full_text)
    # output_file.write(tweet.full_text + "#")
    print(tweet.full_text + "#", file=output_file)
output_file.close()

