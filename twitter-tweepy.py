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
CONSUMER_KEY = ""
CONSUMER_SECRET = ""
ACCESS_TOKEN = ""
ACCESS_TOKEN_SECRET = ""

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
num_quotes = sys.argv[2]
safe_words = sys.argv[3]
# screen_name = "ellonmusk"
timeline = None
try:
    print("Retrieving tweets: " + screen_name)
    timeline = api.user_timeline(screen_name = screen_name, count=200, include_rts=False,tweet_mode="extended")
    # print(timeline)
except:
    sys.exit("Sorry error in querying the screen name")

#open file to write the tweets in 
filename = screen_name+".txt"
output_file = open(filename, "w")
for tweet in timeline:
    # print(tweet.full_text)
    # processed_tweet = erase_links(tweet.full_text)
    # output_file.write(tweet.full_text + "#")
    print((tweet.full_text).lower(), file=output_file)
output_file.close()

#execute the main executable
# first argument filename, second number of quotes
# third argument determines if only non-profanity words allowed
execute_markov_chain = "./markov_chain_quotes {0} {1} {2}".format(filename, num_quotes, safe_words) 
os.system(execute_markov_chain)
