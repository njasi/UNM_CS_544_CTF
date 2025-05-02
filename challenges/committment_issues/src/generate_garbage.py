import subprocess
import os
import random
import time
from faker import Faker


fake = Faker()


def run_git_command(command):
    """
    quick helper command to run git coommands
    """
    result = subprocess.run(
        command, shell=True, check=True, text=True, capture_output=True
    )
    return result.stdout.strip()


def fake_text(length=100):
    """
    wrapper for making fake text
    """
    return fake.text(max_nb_chars=length)


def create_random_file(path, min_len=50, max_len=150):
    """
    make a random file with random content
    """
    with open(path, "w") as f:
        content = fake_text(random.randint(min_len, max_len))
        f.write(content)


def create_random_commit(min_file=1, max_file=4):
    """
    make random commit
    """

    for _ in range(random.randint(min_file, max_file)):
        filename = f"random_file_{fake.user_name()}_{random.randint(100, 999)}.txt"
        create_random_file(filename)

    run_git_command(f"git add -A")
    run_git_command(f'git commit -m "Random commit: {fake.sentence(nb_words=6)}"')


def create_random_branch(min_commits=1, max_commits=6):
    """
    make a random branch with a random amount of commits
    """
    branch_name = f"branch_{fake.word()}_{random.randint(1000, 9999)}"
    run_git_command(f"git checkout -b {branch_name}")

    for _ in range(random.randint(min_commits, max_commits)):
        create_random_commit()

    run_git_command("git checkout main")
    return branch_name


def create_secret_key():
    """
    create secret key file
    """
    # TODO
    pass


def populate_repo():
    """
    populate a random git repo with a secret hidden somewhere inside
    """
    if not os.path.isdir(".git"):
        run_git_command("git init")

    num_commits = random.randint(5, 50)
    num_branches = random.randint(3, 41)

    for _ in range(num_commits):
        create_random_commit()
        time.sleep(random.uniform(0.5, 2.0))

    for _ in range(num_branches):
        create_random_branch()
        time.sleep(random.uniform(1.0, 3.0))

    # todo randomly choose a branch & commit to put this in
    create_secret_key()


if __name__ == "__main__":
    populate_repo()
