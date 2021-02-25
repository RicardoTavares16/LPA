# 3:
- b) não sei resolver o 3 sum mas posso transformá-lo em 3 colineares e a sol. deste problema dá-me a resposta para a soma de 3 elem.

- c) se é impossível resolver 3sum em < O^2 e 3col é uma transformação de 3sum, então também é impossível resolver 3col em < O^2.

- d) function 3Sum (s) {
        sort(s)
        for i = 1 to n-2{

            if(s[i] >= 0){
                return false // se já fiz tudo
            }

            start = i+1
            end = n
            a = s[i]

            while start < end:
                b = s[start];  <= s[end]
            
            if (a + b + c == 0) {
                return true
            }
            else if (a + b + c > 0) {
                end = end - 1
            }
            else {
                start = start + 1
            }
        return false
        }
    }