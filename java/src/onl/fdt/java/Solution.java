package onl.fdt.java;

import javafx.util.Pair;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;

class Solution {
/* for problem on page 583*/
    public static void main(String[] args) {
        Solution s = new Solution();
        int r = s.count(3);
        System.out.println(r);
    }

    private HashSet<Pair<Integer, Integer>> pool;
    private HashSet<HashMap<Integer, HashSet<Integer>>> s;
    public int count(int t) {
        int count = 0;
        this.s(t);
        for (HashMap<Integer, HashSet<Integer>> m : this.s) {
            if (check(m)) {
                ++count;
            }
        }
        return count;
    }

    private boolean check(HashMap<Integer, HashSet<Integer>> i) {
        // j -> k, k -> m; so j should -> m
        for (Integer j : i.keySet()) {
            for (Integer k : i.get(j)) {
                for (Integer m : i.get(k)) {
                    if (!i.get(j).contains(m)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    private HashSet<Pair<Integer, Integer>> p(int t) {
        HashSet<Pair<Integer, Integer>> s = new HashSet<>();
        for (int i = 1; i <= t; ++i) {
            for (int j = 1; j <= t; ++j) {
                s.add(new Pair<>(i, j));
            }
        }
        return s;
    }

    private HashSet<HashMap<Integer, HashSet<Integer>>> s(int t) {
        this.s = new HashSet<>();
        this.pool = this.p(t);
        HashMap<Integer, HashSet<Integer>> m = new HashMap<>();
        for (int i = 1; i <= t; ++i) {
            m.put(i, new HashSet<>());
        }
        this.s.add(m);
        this.g(this.pool.iterator());
        return this.s;
    }

    private void g(Iterator<Pair<Integer, Integer>> i) {
        if (i.hasNext()) {
            HashSet<HashMap<Integer, HashSet<Integer>>> s = new HashSet<>();
            for (HashMap<Integer, HashSet<Integer>> j : this.s) {
                HashMap<Integer, HashSet<Integer>> k = new HashMap<>();
                for (Integer m : j.keySet()) {
                    k.put(m, new HashSet<>(j.get(m)));
                }
                s.add(k);
            }
            Pair<Integer, Integer> c = i.next();
            for (HashMap<Integer, HashSet<Integer>> cs : s) {
                cs.get(c.getKey()).add(c.getValue());
            }
            this.s.addAll(s);
            this.g(i);
        }
    }

}
