package pers.luxiwen.madmiss.data;

import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.RequiredArgsConstructor;

import javax.persistence.*;
import java.sql.Date;

@Data
@RequiredArgsConstructor
@NoArgsConstructor(force = true)
@Entity
public class Messboard {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    private final Integer no;

    @ManyToOne(cascade = {CascadeType.MERGE, CascadeType.REFRESH}, optional = false)
    @JoinColumn(name = "id")
    private User user;
    private final String nickname;
    private final Date releasetime;
    private final String message;
}
