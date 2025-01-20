from enum import Enum

class NodeKinds(Enum):
    EXPRESSION = 1
    NUMBER_LITERAL = 2
    DIVISION_ID = 3
    IDENTIFIER = 4




class Node:
    def __init__(self, value = None,kind = None, children = []):
        self.value = value
        self.kind = kind
        self.children = children
    

class Tree:
    def __init__(self):
        self.root = Node("ROOT")

    def _serialize(self, out_path):
        pass #TODO tree traversal, saved to list and saved to ast file
    
    def _deserialize(self, in_path):
        pass #TODO load ast file into Tree class
    
