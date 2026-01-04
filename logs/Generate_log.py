import random
from datetime import datetime, timedelta

TOTAL_LINES = 15_000_000  # 1 million log lines
START_TIME = datetime(2025, 9, 10, 12, 0, 0)

info_messages = [
    "Application running",
    "Processing request",
    "User login successful",
    "Cache hit",
    "Background job completed",
    "Heartbeat OK",
    "Worker initialized",
    "Cleanup completed"
]

warn_messages = [
    "High memory usage detected",
    "Low disk space on /var",
    "Slow response detected",
    "Configuration value missing, using default",
    "Retry attempt taking longer than expected"
]

error_messages = [
    "Database connection failed",
    "Timeout while reading request",
    "Failed to write to disk",
    "Authentication service unavailable",
    "Connection reset by peer",
    "Disk I/O error",
    "Service dependency unavailable",
    "Permission denied while accessing file",
    "Out of memory condition detected",
    "Invalid response from upstream service"
]

current_time = START_TIME

with open("logs_100k.log", "w", encoding="utf-8") as f:
    for i in range(TOTAL_LINES):
        r = random.random()

        # Realistic distribution
        if r < 0.70:
            level = "INFO"
            msg = random.choice(info_messages)
        elif r < 0.85:
            level = "WARN"
            msg = random.choice(warn_messages)
        else:
            level = "ERROR"
            msg = random.choice(error_messages)

        # Simulate retries: errors repeat
        if level == "ERROR" and random.random() < 0.6:
            msg = random.choice(error_messages)

        line = f"{current_time:%Y-%m-%d %H:%M:%S} {level} {msg}\n"
        f.write(line)

        # Advance time slightly (realistic)
        current_time += timedelta(seconds=random.randint(0, 2))

print("Generated 1,000,000 log lines → logs_100k.log")
