#include "UserDatabase.h"

// IMPLEMENT THESE
UserDatabase::UserDatabase()
{
    // TODO
    _load_factor = 0.75;
    _size = 0;
    _userTable.resize(11);
    _dummy = new UserNode();

}

UserDatabase::UserDatabase(size_t s, double load)
{
    // TODO
    _load_factor = load;
    _size = 0;
    _userTable.resize(s);
    _dummy = new UserNode();
}

UserDatabase::~UserDatabase()
{
    // TODO
    for (size_t i = 0;i < _userTable.size();i++)
    {
        if (_userTable[i] && _userTable[i] != _dummy)
        {
            delete _userTable[i];
        }
    }
    delete _dummy;
}

size_t UserDatabase::size() const
{
    // TODO
    size_t count = 0;
    for (size_t i = 0;i < _userTable.size();i++) {
        if (_userTable[i] != NULL && _userTable[i] != _dummy) {
            count++;
        }
    }

    return count;
}

size_t UserDatabase::capacity() const
{
    // TODO
    size_t cap = _userTable.size();
    return cap;
}

bool UserDatabase::isEmpty() const
{
    // TODO
    if (_size == 0) {
        return true;
    }
    return false;
}



void UserDatabase::addUser(string username) {
    // TODO
    if (userExists(username)) {
        throw UsernameTakenException(username);
    }
    else {
        int size = capacity();
        if ((double)_size / size >= _load_factor) {
            resize(size * 2 + 1);

        }


        int i = (int)hashFunction(username, capacity());

        while (true) {
            if (_userTable[i] == NULL || _userTable[i] == _dummy) {
                UserNode* newnode = new UserNode(username);
                _userTable[i] = newnode;
                _size++;
                return;
            }
            i++;
            i = i % size;
        }
    }
}


void UserDatabase::removeUser(string username)
{
    // TODO
    if ((userExists(username) == false)) {
        throw UserDoesNotExistException(username);
    }
    UserNode* target = getUser(username);
    for (int i = 0;i < _userTable.size();i++) {
        if (_userTable[i] != NULL && _userTable[i] != _dummy) {
            if (userFollows(_userTable[i]->username, username)) {
                unfollow(_userTable[i]->username, username);
            }
        }
    }
    for (int i = 0;i < _userTable.size();i++) {
        if (_userTable[i] == target) {

            _size = _size - 1;

            delete _userTable[i];
            _userTable[i] = _dummy;
            break;
        }
    }




}

UserNode* UserDatabase::getUser(string username) const
{
    // TODO
    if (userExists(username) == 0) {
        throw UserDoesNotExistException(username);
    }


    size_t index = hashFunction(username, _userTable.size());
    while (_userTable[index] != NULL)
    {
        if (_userTable[index]->username == username)
        {
            return _userTable[index];
        }
        index++;
        index = index % _userTable.size();
    }



}

void UserDatabase::resize(size_t size)
{
    // TODO
    vector<UserNode*> old = _userTable;	//kopya
    _userTable.resize(size);
    for (size_t i = 0;i < size;i++) {
        _userTable[i] = NULL;
    }

    _size = 0;
    for (size_t i = 0; i < old.size(); i++) {
        if (old[i] != NULL && old[i] != _dummy) {
            size_t index = hashFunction(old[i]->username, size);
            addUser(old[i]->username);//kullanci kopyalandı
                //folowerleri kopylaa
            _userTable[index]->follows = old[i]->follows;
            delete old[i];

        }
    }


}

void UserDatabase::follow(string username1, string username2)
{
    // TODO

    if ((userExists(username1) == false)) {
        throw UserDoesNotExistException(username1);
    }
    else if ((userExists(username2) == false)) {
        throw UserDoesNotExistException(username2);
    }
    if (userFollows(username1, username2)) {
        throw RedundantActionException(username1, username2, true);
    }
    UserNode* target = getUser(username1);
    target->follows.push_back(username2);




}

void UserDatabase::unfollow(string username1, string username2)
{
    // TODO
    if ((userExists(username1) == false)) {
        throw UserDoesNotExistException(username1);
    }
    else if ((userExists(username2) == false)) {
        throw UserDoesNotExistException(username2);
    }
    if (userFollows(username1, username2) == false) {
        throw RedundantActionException(username1, username2, false);
    }
    UserNode* target = getUser(username1);
    for (int i = 0;i < target->follows.size();i++) {
        if (target->follows[i] == username2) {
            target->follows.erase(target->follows.begin() + i);
        }
    }


}


bool UserDatabase::userExists(string username) const
{
    // TODO
    size_t index = hashFunction(username, _userTable.size());
    while (_userTable[index] != NULL)
    {
        if (_userTable[index]->username == username) return true;

        index++;
        index = index % _userTable.size();
    }
    return false;

}

bool UserDatabase::userFollows(string username1, string username2) const
{
    if ((userExists(username1) == false)) {
        throw UserDoesNotExistException(username1);
    }
    else if ((userExists(username2) == false)) {
        throw UserDoesNotExistException(username2);
    }
    bool flag = false;
    UserNode* target = getUser(username1);
    for (int i = 0;i < target->follows.size();i++) {
        if (target->follows[i] == username2) flag = true;
    }
    return flag;
}

size_t UserDatabase::userFollowerCount(string username) const
{
    if ((userExists(username) == false)) {
        throw UserDoesNotExistException(username);
    }
    int count = 0;
    UserNode* target = getUser(username);
    for (int i = 0;i < _userTable.size();i++) {
        if (_userTable[i] != NULL && _userTable[i] != target && _userTable[i] != _dummy) {
            if (userFollows(_userTable[i]->username, username)) count++;
        }
    }
    return count;
}

size_t UserDatabase::userFollowsCount(string username) const
{
    if ((userExists(username) == false)) {
        throw UserDoesNotExistException(username);
    }
    else {



        return (size_t)getUser(username)->follows.size();
    }
}

vector<string> UserDatabase::getUserList() const
{
    // TODO
    if (isEmpty()) {
        return vector<string>();
    }

    vector<string> damascus;
    for (int i = 0;i < _userTable.size();i++) {
        if (_userTable[i] != NULL && _userTable[i] != _dummy) {
            damascus.push_back(_userTable[i]->username);
        }
    }

    return damascus;
}

void UserDatabase::printAdjacencyMatrix() const
{
    // TODO
    std::vector<std::string> x_axes = getUserList();
    std::vector<std::string> y_axes = getUserList();
    for (int i = 0;i < x_axes.size();i++) {
        for (int j = 0; j < y_axes.size();j++) {


            if (userFollows(x_axes[i], y_axes[j])) {
                std::cout << 1 << " ";
            }
            else {
                std::cout << 0 << " ";
            }

        }
        std::cout << std::endl;
    }
}


int UserDatabase::BFS(string username1, string username2, bool printPath)
{

    if (!userExists(username1)) {
        throw UserDoesNotExistException(username1);
    }
    if (!userExists(username2)) {
        throw UserDoesNotExistException(username2);
    }

    vector<bool> visited(getUserList().size(), false);
    //vector<string> queue;
    queue<string> queue;
    int a = getUserList().size();

    visited[indexfinder(username1)] = true;
    vector<int> distancevect = vector<int>(a);


    int sayac = 0;
    queue.push(username1);


    
    int flag2 = 0;
    while (!queue.empty()) {
        std::string u = queue.front();
        queue.pop();
        if (printPath) {
            std::cout << u << " ";
        }
        if (u == username2) {
            if (printPath) {
                std::cout << std::endl;
            }
            flag2 = 1;
            break;
        }
        vector<string> follower = getUser(u)->follows;
        for (int i = 0;i < (int)follower.size();i++) {
            int indexf = indexfinder(follower[i]);
            if (visited[indexf] == false) {
                distancevect[indexf] = distancevect[indexfinder(u)] + 1;
                visited[indexf] = true;
                queue.push(follower[i]);


            }
        }
    }







    if (flag2) {
        return distancevect[indexfinder(username2)];
    }
    else {
        if (printPath) std::cout << std::endl;
        return -1;
    }
}



int UserDatabase::indexfinder(std::string username) {
    int i = 0;
    vector<string> a = getUserList();
    for (i = 0;i < a.size();i++) {
        if (a[i] == username) {
            break;
        }
    }
    return i;
}

int UserDatabase::DFS(string username1, string username2, bool printPath)
{

    if (!userExists(username1)) {
        throw UserDoesNotExistException(username1);
    }
    if (!userExists(username2)) {
        throw UserDoesNotExistException(username2);
    }


    vector<bool> visited(getUserList().size(), false);
    vector<string> stack;
    int AllRoadsLeadstoRome = -1;


    stack.push_back(username1);
    visited[indexfinder(username1)] = true;


    if (printPath) {
        cout << username1 << " ";
    }



    while (!stack.empty()) {
        string current = stack.back();
        if (current == username2) {

            AllRoadsLeadstoRome++;
            break;

        }

        bool isvisited = false;
        vector<string> follower = getUser(current)->follows;
        for (int i = 0;i < follower.size(); i++) {
            int indexf = indexfinder(follower[i]);

            if (!visited[indexf]) {
                stack.push_back(follower[i]);
                visited[indexf] = true;
                AllRoadsLeadstoRome++;

                if (printPath) cout << follower[i] << " ";


                isvisited = true;
                break;
            }




        }
        if (!isvisited) {
            stack.pop_back();
            AllRoadsLeadstoRome--;
        }
    }
    if (stack.empty() || stack.back() != username2) {
        if (printPath) std::cout << std::endl;
        return -1;
    }
    if (printPath) {
        std::cout << std::endl;
    }

    return AllRoadsLeadstoRome;
}

double UserDatabase::averageBFS()
{
    double sum = 0;
    int size = 0;
    int axes = getUserList().size();
    vector<string> ciguli = getUserList();
    for (int i = 0;i < axes;++i) {
        for (int j = 0;j < axes;++j) {
            if (i != j) {
                int d = BFS(ciguli[i], ciguli[j], false);
                if (d != -1) {
                    sum += d;
                    ++size;
                }
            }
        }
    }
    if (size > 0) {
        return sum / size;
    }
    else {
        return 0.0;
    }


}

double UserDatabase::averageDFS()
{
    double sum = 0;
    int size = 0;
    int axes = getUserList().size();
    vector<string> ciguli = getUserList();
    for (int i = 0; i < axes; ++i) {
        for (int j = 0; j < axes; ++j) {
            if (i != j) {
                int d = DFS(ciguli[i], ciguli[j], false);
                if (d != -1) {
                    sum += d;
                    ++size;
                }
            }
        }
    }
    if (size > 0) {
        return sum / size;
    }
    else {
        return 0.0;
    }
    return 1;
}

vector<string> UserDatabase::getSharedNeighbourhood(string username1, string username2, size_t k)
{
    if (!userExists(username1)) {
        throw UserDoesNotExistException(username1);
    }
    if (!userExists(username2)) {
        throw UserDoesNotExistException(username2);
    }
    vector<string> blu;
    vector<string> red = getUserList();
    int j = red.size();
    for (int i = 0;i < j;i++) {
        if (BFS(username1, red[i], false) < k && BFS(username2, red[i], false) < k) {
            blu.push_back(red[i]);
        }
    }
    return blu;
}