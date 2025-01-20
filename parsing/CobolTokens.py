
_KINDS = ["COOMMENT", "NUMBER", "SYMBOL", "PUNCTUATION", "STRING", "KEYWORD" ]
_TOKEN_DEF = ["VALUE", "KIND", "LINE"]

_PUNCT = {
    "(": 0,
    ")": 1,
    ".": 2,
    "[": 4,
    "]": 5
}

_KEYWORDS = {
    "ACCEPT": 5,	 	 
    "ACCESS": 5,	 	 
    "ACTIVE-CLASS	 	 ": 5,
    "ADD": 5,	 	 
    "ADDRESS": 5,	 	 
    "ADVANCING": 5,	 	 
    "AFTER": 5,	 	 
    "ALIGNED	 	 ": 5,
    "ALL" :5,	 	 
    "ALLOCATE": 5, 	 	 
    "ALPHABET": 5,	 	 
    "ALPHABETIC": 5,	 	 
    "ALPHABETIC-LOWER": 5,	 	 
    "ALPHABETIC-UPPER": 5,	 	 
    "ALPHANUMERIC": 5,	 	 
    "ALPHANUMERIC-EDITED": 5,	 	 
    "ALSO": 5,	 	 
    "ALTER": 5,	 	 
    "ALTERNATE": 5,	 	 
    "AND": 5,	 	 
    "ANY": 5,	 	 
    "ANYCASE	 	 ": 5,
    "APPLY": 5,	 	 
    "ARE": 5,	 	 
    "AREA": 5,	 	 
    "AREAS": 5,	 	 
    "ASCENDING": 5,	 	 
    "ASSIGN": 5,	 	 
    "AT": 5,	 	 
    "AUTHOR": 5,	 	 
    "B-AND	 	 ": 5,
    "B-NOT	 	 ": 5,
    "B-OR	 	 ": 5,
    "B-XOR	 	 ": 5,
    "BASED	 	 ": 5,
    "BASIS": 5,	 	 
    "BEFORE": 5,	 	 
    "BEGINNING": 5,	 	 
    "BINARY": 5,	 	 
    "BINARY-CHAR	 	 ": 5,
    "BINARY-DOUBLE	 	 ": 5,
    "BINARY-LONG	 	 ": 5,
    "BINARY-SHORT	 	 ": 5,
    "BIT	 	 ": 5,
    "BLANK": 5,	 	 
    "BLOCK": 5,	 	 
    "BOOLEAN	 	 ": 5,
    "BOTTOM": 5,	 	 
    "BY": 5,	 	 
    "BYTE-LENGTH": 5,	 	 
    "CALL": 5,	 	 
    "CANCEL": 5,	 	 
    "CBL": 5,	 	 
    "CD	 ": 5,	 
    "CF	 ": 5,	 
    "CH	 ": 5,	 
    "CHARACTER": 5,	 	 
    "CHARACTERS": 5,	 	 
    "CLASS": 5,	 	 
    "CLASS-ID": 5,	 	 
    "CLOCK-UNITS	 ": 5,	 
    "CLOSE": 5,	 	 
    "COBOL": 5,	 	 
    "CODE": 5,	 	 
    "CODE-SET": 5,	 	 
    "COL	 	 ": 5,
    "COLLATING": 5,	 	 
    "COLS	 	 ": 5,
    "COLUMN	 ": 5,	 
    "COLUMNS	 	 ": 5,
    "COM-REG": 5,	 	 
    "COMMA": 5,	 	 
    "COMMON": 5,	 	 
    "COMMUNICATION	 ": 5,	 
    "COMP": 5,	 	 
    "COMP-1": 5,	 	 
    "COMP-2": 5,	 	 
    "COMP-3": 5,	 	 
    "COMP-4": 5,	 	 
    "COMP-5": 5,	 	 
    "COMPUTATIONAL": 5,	 	 
    "COMPUTATIONAL-1": 5,	 	 
    "COMPUTATIONAL-2": 5,	 	 
    "COMPUTATIONAL-3": 5,	 	 
    "COMPUTATIONAL-4": 5,	 	 
    "COMPUTATIONAL-5": 5,	 	 
    "COMPUTE": 5,	 	 
    "CONDITION	 	 ": 5,
    "CONFIGURATION": 5,	 	 
    "CONSTANT	 	 ": 5,
    "CONTAINS": 5,	 	 
    "CONTENT": 5,	 	 
    "CONTINUE": 5,	 	 
    "CONTROL	 ": 5,	 
    "CONTROLS	 ": 5,	 
    "CONVERTING": 5,	 	 
    "COPY": 5,	 	 
    "CORR": 5,	 	 
    "CORRESPONDING": 5,	 	 
    "COUNT": 5,	 	 
    "CRT	 	 ": 5,
    "CURRENCY": 5,	 	 
    "CURSOR	 	 ": 5,
    "DATA": 5,	 	 
    "DATA-POINTER	 	 ": 5,
    "DATE": 5,	 	 
    "DATE-COMPILED": 5,	 	 
    "DATE-WRITTEN": 5,	 	 
    "DAY": 5,	 	 
    "DAY-OF-WEEK": 5,	 	 
    "DBCS": 5,	 	 
    "DE	 ": 5,	 
    "DEBUG-CONTENTS": 5,	 	 
    "DEBUG-ITEM": 5,	 	 
    "DEBUG-LINE": 5,	 	 
    "DEBUG-NAME": 5,	 	 
    "DEBUG-SUB-1": 5,	 	 
    "DEBUG-SUB-2": 5,	 	 
    "DEBUG-SUB-3": 5,	 	 
    "DEBUGGING": 5,	 	 
    "DECIMAL-POINT": 5,	 	 
    "DECLARATIVES": 5,	 	 
    "DEFAULT": 5, 	 	 
    "DELETE": 5,	 	 
    "DELIMITED": 5,	 	 
    "DELIMITER": 5,	 	 
    "DEPENDING": 5,	 	 
    "DESCENDING": 5,	 	 
    "DESTINATION	 ": 5,	 
    "DETAIL	 ": 5,	 
    "DISABLE	 ": 5,	 
    "DISPLAY": 5,	 	 
    "DISPLAY-1": 5,	 	 
    "DIVIDE": 5,	 	 
    "DIVISION": 5,	 	 
    "DOWN": 5,	 	 
    "DUPLICATES": 5,	 	 
    "DYNAMIC": 5,	 	 
    "EC	 	 ": 5,
    "EGCS": 5,	 	 
    "EGI	 ": 5,	 
    "EJECT": 5,	 	 
    "ELSE": 5,	 	 
    "EMI	 ": 5,	 
    "ENABLE	 ": 5,	 
    "END": 5,	 	 
    "END-ACCEPT	 	 ": 5,
    "END-ADD": 5,	 	 
    "END-CALL": 5,	 	 
    "END-COMPUTE": 5,	 	 
    "END-DELETE": 5,	 	 
    "END-DISPLAY	 	 ": 5,
    "END-DIVIDE": 5,	 	 
    "END-EVALUATE": 5,	 	 
    "END-EXEC": 5,	 	 
    "END-IF": 5,	 	 
    "END-INVOKE": 5,	 	 
    "END-JSON": 5,	 	 
    "END-MULTIPLY": 5,	 	 
    "END-OF-PAGE": 5,	 	 
    "END-PERFORM": 5,	 	 
    "END-READ": 5,	 	 
    "END-RECEIVE	 ": 5,	 
    "END-RETURN": 5,	 	 
    "END-REWRITE": 5,	 	 
    "END-SEARCH": 5,	 	 
    "END-START": 5,	 	 
    "END-STRING": 5,	 	 
    "END-SUBTRACT": 5,	 	 
    "END-UNSTRING": 5,	 	 
    "END-WRITE": 5,	 	 
    "END-XML": 5,	 	 
    "ENDING": 5,	 	 
    "ENTER": 5,	 	 
    "ENTRY": 5,	 	 
    "ENVIRONMENT": 5,	 	 
    "EO	 	 ": 5,
    "EOP": 5,	 	 
    "EQUAL": 5,	 	 
    "ERROR": 5,	 	 
    "ESI	 ": 5,	 
    "EVALUATE": 5,	 	 
    "EVERY": 5,	 	 
    "EXCEPTION": 5,	 	 
    "EXCEPTION-OBJECT	 	 ": 5,
    "EXEC": 5,	 	 
    "EXECUTE": 5,	 	 
    "EXIT": 5,	 	 
    "EXTEND": 5,	 	 
    "EXTERNAL": 5,	 	 
    "FACTORY": 5,	 	 
    "FALSE": 5,	 	 
    "FD": 5,	 	 
    "FILE": 5,	 	 
    "FILE-CONTROL": 5,	 	 
    "FILLER": 5,	 	 
    "FINAL	 ": 5,	 
    "FIRST": 5,	 	 
    "FLOAT-EXTENDED	 	 ": 5,
    "FLOAT-LONG	 	 ": 5,
    "FLOAT-SHORT	 	 ": 5,
    "FOOTING": 5,	 	 
    "FOR": 5,	 	 
    "FORMAT	 	 ": 5,
    "FREE": 5, 	 	 
    "FROM": 5,	 	 
    "FUNCTION": 5,	 	 
    "FUNCTION-ID	 	 ": 5,
    "FUNCTION-POINTER": 5,	 	 
    "GENERATE": 5,	 	 
    "GET	 	 ": 5,
    "GIVING": 5,	 	 
    "GLOBAL": 5,	 	 
    "GO": 5,	 	 
    "GOBACK": 5,	 	 
    "GREATER": 5,	 	 
    "GROUP	 ": 5,	 
    "GROUP-USAGE": 5,	 	 
    "HEADING	 ": 5,	 
    "HIGH-VALUE": 5,	 	 
    "HIGH-VALUES": 5,	 	 
    "I-O": 5,	 	 
    "I-O-CONTROL": 5,	 	 
    "ID": 5,	 	 
    "IDENTIFICATION": 5,	 	 
    "IF": 5,	 	 
    "IN": 5,	 	 
    "INDEX": 5,	 	 
    "INDEXED": 5,	 	 
    "INDICATE	 ": 5,	 
    "INHERITS": 5,	 	 
    "INITIAL": 5,	 	 
    "INITIALIZE": 5,	 	 
    "INITIATE	 ": 5,	 
    "INPUT": 5,	 	 
    "INPUT-OUTPUT": 5,	 	 
    "INSERT": 5,	 	 
    "INSPECT": 5,	 	 
    "INSTALLATION": 5,	 	 
    "INTERFACE	 	 ": 5,
    "INTERFACE-ID	 	 ": 5,
    "INTO": 5,	 	 
    "INVALID": 5,	 	 
    "INVOKE": 5,	 	 
    "IS": 5,	 	 
    "JAVA": 5,	 	 
    "JNIENVPTR": 5,	 	 
    "JSON": 5,	 	 
    "JSON-CODE": 5,	 	 
    "JSON-STATUS": 5,	 	 
    "JUST": 5,	 	 
    "JUSTIFIED": 5,	 	 
    "KANJI": 5,	 	 
    "KEY": 5,	 	 
    "LABEL": 5,	 	 
    "LAST	 ": 5,	 
    "LEADING": 5,	 	 
    "LEFT": 5,	 	 
    "LENGTH": 5,	 	 
    "LESS": 5,	 	 
    "LIMIT": 5, 	 	 
    "LIMITS	 ": 5,	 
    "LINAGE": 5,	 	 
    "LINAGE-COUNTER": 5,	 	 
    "LINE": 5,	 	 
    "LINE-COUNTER	 ": 5,	 
    "LINES": 5,	 	 
    "LINKAGE": 5,	 	 
    "LOCAL-STORAGE": 5,	 	 
    "LOCALE	 	 ": 5,
    "LOCK": 5,	 	 
    "LOW-VALUE": 5,	 	 
    "LOW-VALUES": 5,	 	 
    "MEMORY": 5,	 	 
    "MERGE": 5,	 	 
    "MESSAGE	 ": 5,	 
    "METHOD": 5,	 	 
    "METHOD-ID": 5,	 	 
    "MINUS	 	 ": 5,
    "MODE": 5,	 	 
    "MODULES": 5,	 	 
    "MORE-LABELS": 5,	 	 
    "MOVE": 5,	 	 
    "MULTIPLE": 5,	 	 
    "MULTIPLY": 5,	 	 
    "NATIONAL": 5,	 	 
    "NATIONAL-EDITED": 5,	 	 
    "NATIVE": 5,	 	 
    "NEGATIVE": 5,	 	 
    "NESTED	 	 ": 5,
    "NEXT": 5,	 	 
    "NO": 5,	 	 
    "NOT": 5,	 	 
    "NULL": 5,	 	 
    "NULLS": 5,	 	 
    "NUMBER	 ": 5,	 
    "NUMERIC": 5,	 	 
    "NUMERIC-EDITED": 5,	 	 
    "OBJECT": 5,	 	 
    "OBJECT-COMPUTER": 5,	 	 
    "OBJECT-REFERENCE	 	 ": 5,
    "OCCURS": 5,	 	 
    "OF": 5,	 	 
    "OFF": 5,	 	 
    "OMITTED": 5,	 	 
    "ON": 5,	 	 
    "OPEN": 5,	 	 
    "OPTIONAL": 5,	 	 
    "OPTIONS	 	 ": 5,
    "OR": 5,	 	 
    "ORDER": 5,	 	 
    "ORGANIZATION": 5,	 	 
    "OTHER": 5,	 	 
    "OUTPUT": 5,	 	 
    "OVERFLOW": 5,	 	 
    "OVERRIDE": 5,	 	 
    "PACKED-DECIMAL": 5,	 	 
    "PADDING": 5,	 	 
    "PAGE": 5,	 	 
    "PAGE-COUNTER	 ": 5,	 
    "PASSWORD": 5,	 	 
    "PERFORM": 5,	 	 
    "PF	 ": 5,	 
    "PH	 ": 5,	 
    "PIC": 5,	 	 
    "PICTURE": 5,	 	 
    "PLUS	 ": 5,	 
    "POINTER": 5,	 	 
    "POINTER-24 	 	 ": 5,
    "POINTER-31 	 	 ": 5,
    "POINTER-32 ": 5,	 	 
    "POINTER-64 	 	 ": 5,
    "POSITION": 5,	 	 
    "POSITIVE": 5,	 	 
    "PRESENT	 	 ": 5,
    "PRINTING	 ": 5,	 
    "PROCEDURE": 5,	 	 
    "PROCEDURE-POINTER": 5,	 	 
    "PROCEDURES": 5,	 	 
    "PROCEED": 5,	 	 
    "PROCESSING": 5,	 	 
    "PROGRAM": 5,	 	 
    "PROGRAM-ID": 5,	 	 
    "PROGRAM-POINTER	 	 ": 5,
    "PROPERTY	 	 ": 5,
    "PROTOTYPE	 	 ": 5,
    "PURGE	 ": 5,	 
    "QUEUE	 ": 5,	 
    "QUOTE": 5,	 	 
    "QUOTES": 5,	 	 
    "RAISE	 	 ": 5,
    "RAISING	 	 ": 5,
    "RANDOM": 5,	 	 
    "RD	 ": 5,	 
    "READ": 5,	 	 
    "READY": 5,	 	 
    "RECEIVE	 ": 5,	 
    "RECORD": 5,	 	 
    "RECORDING": 5,	 	 
    "RECORDS": 5,	 	 
    "RECURSIVE": 5,	 	 
    "REDEFINES": 5,	 	 
    "REEL": 5,	 	 
    "REFERENCE": 5,	 	
    "REFERENCES": 5,	 	
    "RELATIVE": 5,	 	 
    "RELEASE": 5,	 	 
    "RELOAD": 5,	 	 
    "REMAINDER": 5,	 	 
    "REMOVAL": 5,	 	 
    "RENAMES": 5,	 	 
    "REPLACE": 5,	 	 
    "REPLACING": 5,	 	 
    "REPORT	 ": 5,	 
    "REPORTING	 ": 5,	 
    "REPORTS	 ": 5,	 
    "REPOSITORY": 5,	 	 
    "RERUN": 5,	 	 
    "RESERVE": 5,	 	 
    "RESET": 5,	 	 
    "RESUME	 	 ": 5,
    "RETRY	 	 ": 5,
    "RETURN": 5,	 	 
    "RETURN-CODE": 5,	 	 
    "RETURNING": 5,	 	 
    "REVERSED": 5,	 	 
    "REWIND": 5,	 	 
    "REWRITE": 5,	 	 
    "RF	 ": 5,	 
    "RH	 ": 5,	 
    "RIGHT": 5,	 	 
    "ROUNDED": 5,	 	 
    "RUN": 5,	 	 
    "SAME": 5,	 	 
    "SCREEN	 	 ": 5,
    "SD": 5,	 	 
    "SEARCH": 5,	 	 
    "SECTION": 5,	 	 
    "SECURITY": 5,	 	 
    "SEGMENT	 ": 5,	 
    "SEGMENT-LIMIT": 5,	 	 
    "SELECT": 5,	 	 
    "SELF": 5,	 	 
    "SEND	 ": 5,	 
    "SENTENCE": 5,	 	 
    "SEPARATE": 5,	 	 
    "SEQUENCE": 5,	 	 
    "SEQUENTIAL": 5,	 	 
    "SERVICE": 5,	 	 
    "SET": 5,	 	 
    "SHARING	 	 ": 5,
    "SHIFT-IN": 5,	 	 
    "SHIFT-OUT": 5,	 	 
    "SIGN": 5,	 	 
    "SIZE": 5,	 	 
    "SKIP1": 5,	 	 
    "SKIP2": 5,	 	 
    "SKIP3": 5,	 	 
    "SORT": 5,	 	 
    "SORT-CONTROL": 5,	 	 
    "SORT-CORE-SIZE": 5,	 	 
    "SORT-FILE-SIZE": 5,	 	 
    "SORT-MERGE": 5,	 	 
    "SORT-MESSAGE": 5,	 	 
    "SORT-MODE-SIZE": 5,	 	 
    "SORT-RETURN": 5,	 	 
    "SOURCE	 ": 5,	 
    "SOURCE-COMPUTER": 5,	 	 
    "SOURCES	 	 ": 5,
    "SPACE": 5,	 	 
    "SPACES": 5,	 	 
    "SPECIAL-NAMES": 5,	 	 
    "SQL": 5,	 	 
    "SQLIMS": 5,	 	 
    "STANDARD": 5,	 	 
    "STANDARD-1": 5,	 	 
    "STANDARD-2": 5,	 	 
    "START": 5,	 	 
    "STATUS": 5,	 	 
    "STOP": 5,	 	 
    "STRING": 5,	 	 
    "SUB-QUEUE-1	 ": 5,	 
    "SUB-QUEUE-2	 ": 5,	 
    "SUB-QUEUE-3	 ": 5,	 
    "SUBTRACT": 5,	 	 
    "SUM	 ": 5,	 
    "SUPER": 5,	 	 
    "SUPPRESS": 5,	 	 
    "SYMBOLIC": 5,	 	 
    "SYNC": 5,	 	 
    "SYNCHRONIZED": 5,	 	 
    "SYSTEM-DEFAULT	 	 ": 5,
    "TABLE	 ": 5,	 
    "TALLY": 5,	 	 
    "TALLYING": 5,	 	 
    "TAPE": 5,	 	 
    "TERMINAL	 ": 5,	 
    "TERMINATE	 ": 5,	 
    "TEST": 5,	 	 
    "TEXT	 ": 5,	 
    "THAN": 5,	 	 
    "THEN": 5,	 	 
    "THROUGH": 5,	 	 
    "THRU": 5,	 	 
    "TIME": 5,	 	 
    "TIMES": 5,	 	 
    "TITLE": 5,	 	 
    "TO": 5,	 	 
    "TOP": 5,	 	 
    "TRACE": 5,	 	 
    "TRAILING": 5,	 	 
    "TRUE": 5,	 	 
    "TYPE": 5,	 	 
    "TYPEDEF	 	 ": 5,
    "UNIT": 5,	 	 
    "UNIVERSAL	 	 ": 5,
    "UNLOCK	 	 ": 5,
    "UNSTRING": 5,	 	 
    "UNTIL": 5,	 	 
    "UP": 5,	 	 
    "UPON": 5,	 	 
    "USAGE": 5,	 	 
    "USE": 5,	 	 
    "USER-DEFAULT	 	 ": 5,
    "USING": 5,	 	 
    "UTF-8": 5,	 	 
    "VAL-STATUS	 	 ": 5,
    "VALID	 	 ": 5,
    "VALIDATE	 	 ": 5,
    "VALIDATE-STATUS	 	 ": 5,
    "VALUE": 5,	 	 
    "VALUES": 5,	 	 
    "VARYING": 5,	 	 
    "VOLATILE": 5,	 	 
    "WHEN": 5,	 	 
    "WHEN-COMPILED": 5,	 	 
    "WITH": 5,	 	 
    "WORDS": 5,	 	 
    "WORKING-STORAGE": 5,	 	 
    "WRITE": 5,	 	 
    "WRITE-ONLY": 5,	 	 
    "XML": 5,	 	 
    "XML-CODE": 5,	 	 
    "XML-EVENT": 5,	 	 
    "XML-INFORMATION": 5,	 	 
    "XML-NAMESPACE": 5,	 	 
    "XML-NAMESPACE-PREFIX": 5,	 	 
    "XML-NNAMESPACE": 5,	 	 
    "XML-NNAMESPACE-PREFIX": 5,	 	 
    "XML-NTEXT": 5,	 	 
    "XML-SCHEMA": 5,	 	 
    "XML-TEXT": 5,	 	 
    "ZERO": 5,	 	 
    "ZEROES": 5,	 	 
    "ZEROS": 5
}
def token_value(token):
    return token[_TOKEN_DEF[0]]     
def token_kind(token):
    return token[_TOKEN_DEF[1]]            
def token_line(token):
    return token[_TOKEN_DEF[2]]     

def is_token_of_kind(token ,kind):
    return _KINDS[token_kind(token)] == kind
 