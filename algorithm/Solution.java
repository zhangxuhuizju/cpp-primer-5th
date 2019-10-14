class Main {
    private Set<String> visit = new HashSet<>();
    private List<String> results = new ArrayList<>();
    
    private void removeLeft(String s) {
        int match = 0;
        for(int i=s.length()-1; i>=0; i--) {
            if (s.charAt(i) == ')') match ++;
            else if (s.charAt(i) == '(') match --;
            if (match < 0) {
                for(int j=s.length()-1; j>=i; j--) {
                    if (s.charAt(j) != '(') continue;
                    String r = s.substring(0, j) + s.substring(j+1);
                    if (visit.contains(r)) continue;
                    visit.add(r);
                    removeLeft(r);
                }
                return;
            }
        }
        results.add(s);
    }
    private void removeRight(String s) {
        int match = 0;
        for(int i=0; i<s.length(); i++) {
            if (s.charAt(i) == '(') match ++;
            else if (s.charAt(i) == ')') match --;
            if (match < 0) {
                for(int j=0; j<=i; j++) {
                    if (s.charAt(j) != ')') continue;
                    String r = s.substring(0, j) + s.substring(j+1);
                    if (visit.contains(r)) continue;
                    visit.add(r);
                    removeRight(r);
                }
                return;
            }
        }
        if (match == 0) {
            results.add(s);
            return;
        }
        removeLeft(s);
    }
    public List<String> removeInvalidParentheses(String s) {
        removeRight(s);
        return results;
    } 
}