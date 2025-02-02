from Coblex import lex
from CobolTokens import token_value, is_token_of_kind, token_line, _KINDS
import ASTser 
class RecDParser:

    S = 0
    A = 1
    B = 2
    C = 3
    D = 4
    E = 5
    F = 6
    SYMBOL = _KINDS[2]
    def peek(self):
        return self.stack[len(self.stack)-1]
    def pop(self):
        self.stack.pop()
    def add(self, el):
        self.stack.append(el)

    def __init__(self, tokens = []):
        self.tokens = tokens 
        self.current = None
        self.table = [
            {
                "ID": [self.fA, "ID"],
                "IDENTIFICATION": False
            },
            {
                "PROG-ID": ""
            },
            {
                ".": "",
                self.SYMBOL: ""
            },
            {
                self.SYMBOL: ""
            }
        ]
        self.stack = []
    def fA(self):
        print("parsing A rule")
    def source(self):
        self.stack.append("$")
        self.nextToken()
        if things := self.table[self.S].get(token_value(self.current), False):
            for thing in things:
                self.stack.append(thing)
        else:
            self.syntax_error(self.current, "something")
            
        while self.peek() == token_value(self.current):
            self.nextToken()
            self.pop()

        self.peek()()
        
    
         
    def nextToken(self):
        if len(self.tokens) > 0:
            self.current = self.tokens.pop(0)
        else:
            self.current = None

    def skipXtoken(self, x):
        for i in range(x):
            if i == x-1:
                self.nextToken()
            else:
                self.tokens.pop(0)

    def matchTokenWithAny(self, token, *others):
        for other in others:
            if other == token_value(token):
                self.nextToken()
                return True
        self.syntax_error(token, [el for el in others])
        return False
    
    def matchLookAheadWith(self, la_offset, other):
        return token_value(self.tokens[la_offset]) == other

    def syntax_error(self, token, expected):
        print("ERROR invalid token", token_value(token), "on line", token_line(token), f"expected any of [{ ','.join(expected) }]" )
        
    def Optional_dot(self):
        if token_value(self.current) == ".":
            self.nextToken()
    
    def program_id_cobol_source_program(self) :
        def Optional2():
            if Optional3() and not token_value(self.current) == "INITIAL":
                self.syntax_error(self.current, ["INITIAL"])
                return None
            self.nextToken()
    
            Optional4()
        def Optional3():
            if token_value(self.current) == "IS":
                self.nextToken()
                return True
            return False
        def Optional4():
            if token_value(self.current) == "PROGRAM":
                self.nextToken()

        ############ START ###################       
        # progid = ASTser.ProgramID()
        if not self.matchTokenWithAny(self.current, "PROGRAM-ID"):
            return None
        self.Optional_dot()
        if is_token_of_kind(self.current, "SYMBOL"):
            # progid.ID = token_value(self.current)
            self.nextToken()
        Optional2()
        self.Optional_dot()
        

    def cobol_source_program(self):
        self.nextToken()
        if not self.matchTokenWithAny(self.current, "ID", "IDENTIFICATION"):
            return
        if not self.matchTokenWithAny(self.current, "DIVISION"):
            return
        if not self.matchTokenWithAny(self.current, "."):
            return
        programid = self.program_id_cobol_source_program()
        if programid != None:
            print(programid.ID, programid.initial)
        


def main():
    tokens = lex()
    parser  = RecDParser(tokens)
    # print(tokens)
    # tree = Tree()
    stack = []
    # for i, current in enumerate(tokens):
    parser.source()

    

if __name__ == "__main__":
    main()