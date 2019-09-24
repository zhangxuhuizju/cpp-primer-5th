#include <string>
#include <set>
#include <iostream>

class Folder;

class Message{
    friend class Folder;
    friend void swap(Message &, Message&);
public:
    explicit Message(const std::string &str = ""):
            contents(str){}
    void print_debug(){
        std::cout << contents << std::endl;
    }
    Message(const Message &);   //拷贝构造函数
    Message& operator=(const Message &);
    ~Message();
    void save(Folder&);
    void remove(Folder&);
private:
    std::string contents;
    std::set<Folder*> folders;      //包含message信息的folder

    void add_to_folders(const Message&);
    void remove_from_folders();
    void addFold(Folder *fld){folders.insert(fld);}
    void remFold(Folder *fld) {folders.erase(fld);}
};

class Folder{
    friend class Message;
    friend void swap(Folder&, Folder&);
public:
    Folder() = default;
    Folder(const Folder&);
    Folder& operator=(const Folder&);
    void print_debug();
    ~Folder();
private:
    std::set<Message*> messages;

    void remove_from_messages();
    void add_to_messages(const Folder&);
    void addMsg(Message *msg){messages.insert(msg);}
    void remMsg(Message *msg) {messages.erase(msg);}
};

void Message::save(Folder &f) {
    folders.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder &f) {
    folders.erase(&f);
    f.remMsg(this);
}

void Message::add_to_folders(const Message &msg) {
    for (auto f : msg.folders)
        f->addMsg(this);
}

Message::Message(const Message &msg):
        contents(msg.contents), folders(msg.folders) {
    add_to_folders(msg);    //将本消息添加到msg指向的文件夹里面
}

void Message::remove_from_folders() {
    for (auto f : folders)
        f->remMsg(this);
}

Message::~Message() {
    remove_from_folders();
}

Message& Message::operator=(const Message &msg) {
    remove_from_folders();
    contents = msg.contents;
    folders = msg.folders;
    add_to_folders(msg);
    return *this;
}

void swap(Message &lhs, Message &rhs) {
    lhs.remove_from_folders();
    rhs.remove_from_folders();
    std::swap(lhs.contents, rhs.contents);
    std::swap(lhs.folders, rhs.folders);
    lhs.add_to_folders(lhs);
    rhs.add_to_folders(rhs);
}

Folder::Folder(const Folder& f):messages(f.messages) {
    add_to_messages(f);
}

Folder& Folder::operator=(const Folder &rhs) {
    remove_from_messages();
    messages = rhs.messages;
    add_to_messages(rhs);
    return *this;
}

Folder::~Folder() {
    remove_from_messages();
}

void Folder::add_to_messages(const Folder &f) {
    for(auto msg : f.messages)
        msg->addFold(this);
}

void Folder::remove_from_messages() {
    for(auto msg : messages)
        msg->remFold(this);
}

void swap(Folder &lhs, Folder &rhs) {
    lhs.remove_from_messages();
    rhs.remove_from_messages();
    std::swap(lhs.messages, rhs.messages);
    lhs.add_to_messages(lhs);
    rhs.add_to_messages(rhs);
}

void Folder::print_debug()
{
    for (auto m : messages) 
        std::cout << m->contents << "-----";
    std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
    Message firstMail("hello");
    Message signInMail("welcome to cpp primer");
    Folder mailBox;
 
    firstMail.print_debug(); // print: "hello"
    firstMail.save(mailBox); // send to mailBox
    mailBox.print_debug();   // print: "hello"
 
    signInMail.print_debug(); // print "welcome to cppprimer"
    signInMail.save(mailBox); // send to mailBox
    mailBox.print_debug();    // print "welcome to cppprimer hello"
 
    firstMail = firstMail;   // test for assignment to self.
    firstMail.print_debug(); // print "hello"
    mailBox.print_debug();   // print "welcome to cppprimer hello"

    swap(firstMail, signInMail);
    firstMail.print_debug();
    signInMail.print_debug();

    mailBox.print_debug();

    return 0;
}
