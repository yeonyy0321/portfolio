import logging
import sys

def setup_logger(logger_name, log_level=logging.DEBUG, log_format=None, log_file=None):
    """
    Set up a logger with the specified name, log level, format, and file.

    Args:
    - logger_name (str): The name of the logger.
    - log_level (int): The log level (e.g., logging.DEBUG, logging.INFO).
    - log_format (str): The log format.
    - log_file (str): The path to the log file.

    Returns:
    - logging.Logger: The configured logger.
    """
    logger = logging.getLogger(logger_name)
    logger.setLevel(log_level)

    formatter = logging.Formatter(log_format or '%(asctime)s - %(name)s - %(levelname)s - %(message)s')

    # Console handler
    console_handler = logging.StreamHandler(sys.stdout)
    console_handler.setFormatter(formatter)
    logger.addHandler(console_handler)

    # File handler
    if log_file:
        file_handler = logging.FileHandler(log_file)
        file_handler.setFormatter(formatter)
        logger.addHandler(file_handler)

    return logger

# Example usage:
# logger = setup_logger(__name__, log_level=logging.DEBUG, log_format=None, log_file='app.log')
# logger.debug('Debug message')
# logger.info('Info message')
# logger.warning('Warning message')
# logger.error('Error message')
# logger.critical('Critical message')
