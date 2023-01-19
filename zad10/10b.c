Position createNew(char* ime)
{
    Position n = NULL;
    n = (Position)malloc(sizeof(tree));
    if (!n)
        return ERROR;
    strcpy(n->name, ime);
    n->child = NULL;
    n->sibling = NULL;
    return n;
}
