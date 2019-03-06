void listAll(const MenuItem* m, string path) // two-parameter overload
{
    if (m->menuItems() == nullptr || m->menuItems()->empty())
        return;

    vector<MenuItem*>::const_iterator it;
    for (it = m->menuItems()->begin(); it != m->menuItems()->end(); it++) {
        string name = (*it)->name();
        cout << (path + name) << endl;
        listAll(*it, path + name + "/");
    }
}