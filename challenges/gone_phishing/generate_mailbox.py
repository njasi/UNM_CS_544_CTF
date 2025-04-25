import mailbox
from faker import Faker
from email.message import EmailMessage
from email.utils import format_datetime, formatdate, make_msgid
import random

fake = Faker()

PHISHING_SUBJECT = "URGENT: Low email storage space."
PHISHING_CONTENT = """\
<html>
  <body>
    <p>Dear user,</p>
    <p>Your mailbox has reached <b>98%</b> of its storage capacity. Incoming emails may be delayed or rejected.</p>
    <p>To continue receiving mail without interruptions, please <a href="https://notyourcompany.com/login" style="color:#0066cc;">https://yourcompany.com/login</a>.</p>
    <p>Thank you,<br>
    Central IT</p>
  </body>
</html>
"""


def generate_spam_subject():
    options = [
        "🔥 You won't believe this deal!",
        "We've been trying to reach you about you car's extended warranty"
        "💰 Make $$$ working from home!",
        "Your account has been selected!",
        "Congratulations! You've won!",
        "Urgent: Action Required",
        "Exclusive Offer Inside",
        "Lose 20 pounds in 2 weeks",
        "🔐 Secure your password now",
        "This is not a drill!",
        "Check this out now >>>",
        "Re: Your invoice is overdue",
        "Important: Confirm your payment details immediately",
        "🔥 Just launched: Earn $1,000 a week from home!",
        "You have 1 new voice message (click to listen)",
        "Don't miss out! Your gift card expires tonight",
        "FWD: Still waiting on your bank info",
        "Hi {name}, is this really your account?",
        "Warning: Your account has been compromised!",
        "Claim your $500 Costco voucher now!",
        "Congrats! You've been selected for a free iPhone 15",
        "Schedule your COVID-19 compensation payout",
        "Re: Final notice on your car warranty",
        "Exclusive deal just for you (open now!)",
        "Your package couldn't be delivered — see details",
        "Proof of payment attached — please review",
        "Complete this survey = Get $100 instantly",
        "💼 Work from anywhere — start earning today",
        "🚨 Your PayPal account has been suspended",
        "URGENT: Action required to avoid account lock",
        "New crypto investment alert - 500% ROI 💹",
    ]
    return random.choice(options)


def generate_spam_content():
    templates = [
        "Hi there! I have an amazing opportunity for you. Make money fast by signing up here: {}",
        "You have been selected for a special gift. Click here to claim: {}",
        "This is not spam. We really want you to see this amazing product: {}",
        "Your account has suspicious activity. Login immediately to secure it: {}",
        "You've won a free trip to the Bahamas! Confirm here: {}",
        "Your package delivery failed due to an address issue. Update your information here: {}",
        "You've been selected to win a $100 Amazon gift card. Start your claim now: {}",
        "We noticed suspicious activity on your account. Please verify your identity here: {}",
        "Your subscription expires today. Renew now to avoid service disruption: {}",
        "Congratulations! Claim your free iPhone 15 before it expires: {}",
        "Payment failed due to outdated billing info. Update now to restore service: {}",
        "Your car warranty has expired. Reactivate your coverage here: {}",
        "Someone sent you a private message! View it securely now: {}",
        "You have a secure document waiting. Access it now: {}",
        "Your PayPal account has been locked. Unlock it by verifying your account: {}",
        "Start earning money from home today! Apply for remote jobs now: {}",
        "Submit your details to receive your approved refund: {}",
        "Unclaimed rewards are waiting in your account. Redeem here: {}",
        "A Walmart gift card has been reserved for you. Confirm to receive: {}",
        "Your email storage is almost full. Upgrade now to prevent data loss: {}",
        "You've received a fax document. View it securely online: {}",
        "We received your job application. Upload your resume to complete submission: {}",
        "A new device logged into your crypto wallet. Secure your funds immediately: {}",
        "You're eligible for a tax refund. Submit your claim securely: {}",
        "Reset your password now to prevent account lockout: {}",
    ]
    url = fake.uri()
    return random.choice(templates).format(url)


def generate_spam_email_address():
    # could change back to the faker ones idk
    domains = ["fastcash.biz", "offers-now.net", "secure-login.info", "gift-center.co"]
    username = fake.user_name() + str(random.randint(10, 999))
    return f"{username}@{random.choice(domains)}"


def make_email(mbox, mailbox_owner, subject=None, content=None, sender=None):
    msg = EmailMessage()
    msg["From"] = sender or generate_spam_email_address()
    msg["To"] = mailbox_owner
    msg["Subject"] = subject or generate_spam_subject()

    if content and content.strip().startswith("<html"):
        msg.add_alternative(content, subtype="html")
    else:
        msg.set_content(content or generate_spam_content())

    random_date = fake.date_time_between(start_date="-5y", end_date="now")
    msg.set_unixfrom(
        f"From {msg['From']} {formatdate(random_date.timestamp(), localtime=True)}"
    )
    msg["Date"] = format_datetime(random_date)
    msg["Message-ID"] = make_msgid()

    mbox.add(msg)


def main():
    mbox = mailbox.mbox("mailbox.mbox")
    mailbox_owner = fake.email()

    # Generate many spam emails
    for _ in range(149):
        make_email(mbox, mailbox_owner)

    make_email(
        mbox,
        mailbox_owner,
        subject=PHISHING_SUBJECT,
        content=PHISHING_CONTENT,
        sender="support@yourcorp.gmail.com",
    )

    for _ in range(50):
        make_email(mbox, mailbox_owner)

    mbox.flush()
    mbox.close()


main()
