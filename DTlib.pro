TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    object.cpp \
    exception.cpp \
    DTString.cpp

HEADERS += \
    Object.h \
    List.h \
    SeqList.h \
    StaticList.h \
    Array.h \
    StaticArray.h \
    Exception.h \
    DynamicArray.h \
    LinkList.h \
    StaticLinkList.h \
    Pointer.h \
    SmartPointer.h \
    SharedPointer.h \
    CircleList.h \
    DualLinkList.h \
    LinuxList.h \
    DualCircleList.h \
    Stack.h \
    StaticStack.h \
    LinkStack.h \
    Queue.h \
    StaticQueue.h \
    LinkQueue.h \
    DTString.h \
    Sort.h \
    Tree.h \
    TreeNode.h \
    GTreeNode.h \
    GTree.h \
    BTreeNode.h \
    BTree.h \
    Graph.h \
    MatrixGraph.h \
    ListGraph.h
