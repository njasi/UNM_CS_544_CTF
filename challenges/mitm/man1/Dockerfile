# Use official Python base image
FROM python:3.11-slim

# Set environment variables
ENV PYTHONDONTWRITEBYTECODE=1
ENV PYTHONUNBUFFERED=1

# Set working directory
WORKDIR /app

# Copy script into container
COPY app.py .

# Install required packages
RUN pip install requests

# Run the script
CMD ["python", "app.py"]