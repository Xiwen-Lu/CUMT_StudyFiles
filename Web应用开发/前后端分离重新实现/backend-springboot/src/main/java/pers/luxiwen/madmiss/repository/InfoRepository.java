package pers.luxiwen.madmiss.repository;

import org.springframework.data.repository.CrudRepository;
import org.springframework.data.rest.core.annotation.RestResource;
import pers.luxiwen.madmiss.data.Info;

import java.util.List;

public interface InfoRepository extends CrudRepository<Info, Integer>{
    List<Info> findAllBySchool(String SchoolName);

    //取消方法暴露
    @Override
    @RestResource(exported = false)
    void deleteAll();

}