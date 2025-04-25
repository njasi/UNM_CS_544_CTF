import mailbox

from faker import Faker
from email.message import EmailMessage
from email.utils import format_datetime, formatdate

fake = Faker()

PHISHING_SUBJECT = "Low email storage space urgent."
PHISHING_CONTENT = ""


def make_email(mbox, mailbox_owner, subject=None, content=None):
    """
    Make a fake email and add it to the mailbox
    """
    msg = EmailMessage()
    msg["From"] = fake.email()
    msg["To"] = mailbox_owner
    msg["Subject"] = fake.sentence(nb_words=6) if subject is None else subject
    msg.set_content(fake.paragraph(nb_sentences=5) if content is None else content)

    random_date = fake.date_time_between(start_date="-5y", end_date="now")
    msg.set_unixfrom(
        f"From {msg['From']} {formatdate(random_date.timestamp(), localtime=True)}"
    )
    msg["Date"] = format_datetime(random_date)

    mbox.add(msg)


def main():
    mbox = mailbox.mbox("mailbox.mbox")
    mailbox_owner = fake.email()

    # generate enough so its not super obvious which is the phishing
    for _ in range(199):
        make_email(mbox, mailbox_owner)

    make_email(mbox, mailbox_owner, subject=PHISHING_SUBJECT, content=PHISHING_CONTENT)

    mbox.flush()
    mbox.close()


main()
