package pers.luxiwen.madmiss.service;

import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.util.Assert;
import pers.luxiwen.madmiss.data.User;
import pers.luxiwen.madmiss.repository.UserRepository;



@SpringBootTest
class UserRepositoryUserDetailsServiceTest {

    @Autowired
    private UserRepository userRepository ;

    @Test
    void loadUserByUsername() {
        User user = userRepository.findUserById("1");
        Assert.isTrue(user.getPassword().equals("1"),"判断密码是否相等");
        Assert.isTrue(user.getRole().equals("admin"),"角色类型");
    }
}