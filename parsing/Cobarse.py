from Coblex import lex
from CobolTokens import token_value, is_token_of_kind, token_line
# from parsing.ASTser import Tree, Node, NodeKinds
class RecDParser:

    def __init__(self, tokens = []):
        self.tokens = tokens 
        self.current = None
         
    def nextToken(self):
        if len(self.tokens) > 0:
            self.current = self.tokens.pop(0)
        else:
            self.current = None
        
    def matchLookAHeadX(self, matchstr, offset = 0):
        return token_value(self.tokens[offset]) == matchstr
    def syntax_error(self, token, expected):
        print("ERROR invalid token ", token_value(token), "on line ", token_line(token), f" expected any of [{ ','.join(expected) }]" )
              
    def matchAnyTokens(self, token, others, doPrintError=True):
        for other in others:
            if token_value(token) == other:
                self.nextToken()
                print(token)
                return True
        if doPrintError:
            self.syntax_error(token , others)
    
    def program(self):
        self.nextToken()
        if not self.matchAnyTokens(self.current, ["ID", "IDENTIFICATION"]):
            return
        if not self.matchAnyTokens(self.current, ["DIVISION"]):
            return
        if not self.matchAnyTokens(self.current, ["."]):
            return
        
        print("done")

    
   



def main():
    tokens = lex()
    parser  = RecDParser(tokens)
    # print(tokens)
    # tree = Tree()
    stack = []
    # for i, current in enumerate(tokens):
    parser.program()

    

if __name__ == "__main__":
    main()