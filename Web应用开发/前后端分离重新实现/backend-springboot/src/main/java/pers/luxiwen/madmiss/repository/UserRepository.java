package pers.luxiwen.madmiss.repository;

import org.springframework.data.repository.CrudRepository;
import pers.luxiwen.madmiss.data.User;

public interface UserRepository extends CrudRepository<User,String> {
//   除了扩展CrudRepository所得到的CRUD操作之外，还定义根据用户名查找user方法，会在用户详情中获取
//    User findById(String username);
    User findUserById(String username);
}
