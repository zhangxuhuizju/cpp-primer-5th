class Solution {
    public int lengthOfLongestSubstring(String s) {
        int result = 1;
        if (s.length() <= 1) return s.length();
        HashMap<Character, Integer> hashMap = new HashMap<>();
        int left = 0, right = 0, temp;
        while (right < s.length()) {
            if(hashMap.get(s.charAt(right)) != null) {
                temp = left;
                left = hashMap.get(s.charAt(right)) + 1;
                for (int i = temp; i < left; ++i)
                    hashMap.remove(s.charAt(i));
            }
            hashMap.put(s.charAt(right), right);
            right++;
            if (right - left > result) result = right - left;
        }
        return result;
    }
}