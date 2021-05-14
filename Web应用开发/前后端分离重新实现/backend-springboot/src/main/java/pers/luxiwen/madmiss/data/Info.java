package pers.luxiwen.madmiss.data;

import lombok.AccessLevel;
import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.RequiredArgsConstructor;

import javax.persistence.*;
import java.sql.Date;

@Data
@RequiredArgsConstructor
@NoArgsConstructor(force = true)
@Entity
@Table(name = "info")
public class Info {
    //注意hibernate会将大写字符改成_+小写字符，所以这里全部使用小写字符
    //在MySQL中，大小写不敏感，因而修改java中代码最方便
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private final Integer no;
    private final String school;
    private final String schoolhomepage;
    private final Date summerapplyfinishtime;
    private final Date summeractivitystart;
    private final Date summeractivityfinish;
    private final Integer recommendationletternum;
    @Column(name = "preachlink")
    private final String PreachLink;
    private final String others;


}