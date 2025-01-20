

from enum import Enum

filepath = r'C:\Users\Administrator\Documents\Testing\LegacySearchEngine\cos_subset.csv'

######################## DYNAMIC LINE HEADER HANDLING ###################


__LINE__ = {}
FILE_NAME = PARENT = CHILD = LINK_TYPE = FILE_TYPE = WORKPACKAGE = FILE_PATH = None 

def compute_header_indexes():
    global FILE_NAME, PARENT, CHILD, LINK_TYPE, FILE_TYPE, WORKPACKAGE, FILE_PATH
    
    FILE_NAME   = __LINE__.get('file', None)
    PARENT      = __LINE__.get('parents', None)
    CHILD       = __LINE__.get('children', None)
    LINK_TYPE   = __LINE__.get('linktype', None)
    FILE_TYPE   = __LINE__.get('fileornodetype', None)
    WORKPACKAGE = __LINE__.get('workpackagenames', None)
    FILE_PATH   = __LINE__.get('path', None)
    
def readHeader(lines):
    global __LINE__
    # Read Header
    headers = lines[0].split(";") 
    for i, header in enumerate(headers):
        header = header.lower().strip().replace(" ", "") 
        if header != None:
            __LINE__[header] = i
    compute_header_indexes()
##########################################################################



class NodeType(Enum):
    COBOL = 0
    PF = 1
    LF = 2
    CL = 3
    C = 4
    DSPF = 5
    
    UNKNOWN = 99
    
__FILETYPES__ = {
    "UNK": NodeType.UNKNOWN,
    "COB": NodeType.COBOL,
    "CL": NodeType.CL,
    "DSPF": NodeType.DSPF,
    "C": NodeType.C,
    "PF": NodeType.PF
}

class TreeNode:
    def __init__(self, name, type:str) -> None:
        self.id = id
        self.name = name
        self.localpath=None
        self.children: dict[str, list[TreeNode]] = {}
        self.parents = {}
        self.type = __FILETYPES__.get(type.upper(), __FILETYPES__.get("UNK"))
        
def readNextLine(lines, lp):
    eof = False
    if lp < len(lines)-1:
        lp += 1
    else:
        eof = True
    
    return (lines[lp].split(";"), lp, eof)

def buildTreeFromJSON():
    pass

def recDisplayChildren(node:TreeNode, type,depth:int):
    st = ""
    for i in range(depth):
        st+="\t"
    if len(node.children) <= 0 or depth > 5:
        print(st + node.name + " " + str(depth))
        return
    for child in node.children.get(type, []):
        recDisplayChildren(child, NodeType.COBOL.name, depth+1)
        
    
def buildTreeFromCSV():
    NodesMap: dict[str:TreeNode] = {}
    with open(filepath, "r+", encoding="utf-8") as infile:
        ROOT = TreeNode("ROOT", "UNK")
        lines = infile.readlines()
        # Header part
        readHeader(lines)
        
        # Read from 1 to eof
        line_cursor = 0
        current_node = None
        eof = False
        while(not eof):
            line, line_cursor, eof = readNextLine(lines, line_cursor)
            # New Node
            if len(line[FILE_NAME]) > 0:
                node = TreeNode(line[FILE_NAME], line[FILE_TYPE])
                NodesMap[node.name] = node
                current_node = node
            else:
                while(not eof and len(line[FILE_NAME]) <= 0):
                    if current_node == None:
                        break
                    if(len(line[PARENT]) > 0):
                        n = NodesMap.get(line[PARENT], False)
                        if not n:  
                            n = TreeNode(line[PARENT], line[FILE_TYPE])
                            NodesMap[n.name] = n
                        if n.type != NodeType.UNKNOWN:
                            current_node.parents.setdefault(n.type.name, []).append(n)
                            
                    elif len(line[CHILD]) > 0:
                        n = NodesMap.get(line[CHILD], False)
                        if not n:
                            n = TreeNode(line[CHILD], line[FILE_TYPE])
                            NodesMap[n.name] = n
                        if n.type != NodeType.UNKNOWN:
                            current_node.children.setdefault(n.type.name, []).append(n)
    
                    line, line_cursor, eof = readNextLine(lines, line_cursor)
                line_cursor -= 1

        for node in NodesMap.keys():
            current_node = NodesMap[node]
            if current_node and len(current_node.parents) <= 0:
                ROOT.children.setdefault(current_node.type.name, []).append(current_node)
    
    
    #Display Tree
    print(ROOT.children)
    for tnode in ROOT.children.get(NodeType.COBOL.name, []):
        print(tnode.name + len(tnode.parents))
        # recDisplayChildren(tnode, NodeType.COBOL.name,0)
        
        


    return












if __name__ == "__main__":
    buildTreeFromCSV()    
    
    
    # print("Entry point is LSE.py")
    # exit(1)
else:
    pass