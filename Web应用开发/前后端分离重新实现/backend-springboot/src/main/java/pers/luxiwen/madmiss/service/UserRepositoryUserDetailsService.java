package pers.luxiwen.madmiss.service;

import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.stereotype.Service;
import pers.luxiwen.madmiss.data.User;
import pers.luxiwen.madmiss.repository.UserRepository;

@Slf4j
@Service
public class UserRepositoryUserDetailsService implements UserDetailsService {
    @Autowired
    private UserRepository userRepo;

    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        User user = userRepo.findUserById(username);
        log.info(user.toString());
        if(user != null){
            return user;
        }
        throw new UsernameNotFoundException("User: "+username+" not found");

    }
}
