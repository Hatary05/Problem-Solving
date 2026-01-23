vector<int> lst;
    while(q --> 0) {
        int op; cin >> op;
        if(op == 1) {
            int x; cin >> x;
            auto it = upper_bound(all(lst), x);
            lst.insert(it, x);
        }
        else if(op == 2) {
            int x; cin >> x;
            if(lst.empty()) {
                cout << -1 << '\n';
                continue;
            }

            auto search = [&](ll x) -> pair<optional<int>, optional<int>> {
                auto R = upper_bound(all(lst), x);
                optional<int> l, r;
                if(R != lst.end()) r = *R;
                if(R != lst.begin()) l = *prev(R);
                return {l, r};
            };
            auto [l, r] = search(x);

            const int INF = (1LL << 23);
            int ret = INF;
            if(l) ret = min(ret, abs(x - *l));
            if(r) ret = min(ret, abs(x - *r));
            cout << ret << '\n';
        }
    }
