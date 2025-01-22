template <typename T1, typename T2>
struct Node {
    T1 key;
    T2 value;
    Node* next;
    explicit Node(T1 key) : key(key), value(T2()), next(nullptr) {}
    Node(T1 key, T2 value) : key(key), value(value), next(nullptr) {}
};

class Solution {
    std::hash<string> hasher;
    Node<string, string>** table = new Node<string, string>*[100];
public:

    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        auto index = hasher(longUrl)%100;
        std::cout<<index<<'\n';
        table[index] = new Node<string, string>(longUrl);
        string url = "http://tinyurl.com/" + to_string(index);
        std::cout<<url<<"\n\n";
        return url;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        string sindex = shortUrl.substr(19);
        std::cout<<sindex<<'\n';
        auto size = sindex.length();
        std::cout<<size<<'\n';
        int index = 0;
        int j = 0;
        for (auto i = sindex.rbegin(); i != sindex.rend(); ++i) {
            auto c = *i;
            std::cout<<c<<'\n';
            index += (c-48)*pow(10,j);
            ++j;
        }
        std::cout<<index<<'\n';
        return table[index]->key;
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));