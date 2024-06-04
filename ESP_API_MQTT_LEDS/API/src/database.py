import sqlite3


class SqliteDB:
    def __init__(self):
        self.__db_name = '../local.db'
        self.__connection = sqlite3.connect(self.__db_name)

    def execute_query(self, query_statement: str, args=None) -> list:
        cursor = self.__connection.cursor()
        try:
            if args:
                cursor.executemany(query_statement, args)
            else:
                cursor.execute(query_statement)
            self.__connection.commit()
            return cursor.fetchall()
        except sqlite3.Error as e:
            print(e)

    def close_connection(self):
        self.__connection.close()


def create_device_table(engine: SqliteDB):
    stmt = ("""
            CREATE TABLE IF NOT EXIST Devices(
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            device_name TEXT NOT NULL, 
            mac_address TEXT NOT NULL,
            user_id INTEGER,
            FOREIGN KEY (user_id) REFERENCES Users(id)
            )""")
    engine.execute_query(stmt)


def create_user_table(engine: SqliteDB):
    stmt = """
        CREATE TABLE IF NOT EXISTS Users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL
        )
    """
    engine.execute_query(stmt)


def create_color_leds_table(engine: SqliteDB):
    stmt = """
            CREATE TABLE IF NOT EXISTS Colors(
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            color_series TEXT NOT NULL,
            user_id INTEGER,
            FOREIGN KEY (user_id) REFERENCES Users(id)
            )
        """
    engine.execute_query(stmt)
