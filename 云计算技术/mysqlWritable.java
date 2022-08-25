package simpleHadoop;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import org.apache.hadoop.io.Writable;
import org.apache.hadoop.mapreduce.lib.db.DBWritable;

public class mysqlWritable  implements DBWritable{
    private String name;
    private int wCount;

    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }
    public int getwCount() {
        return wCount;
    }
    public void setwCount(int wCount) {
        this.wCount = wCount;
    }

    @Override
    public void readFields(ResultSet rs) throws SQLException {
//        this.name = rs.getString(1);
//        this.wCount = rs.getInt(2);
        return;
    }
    @Override
    public void write(PreparedStatement ps) throws SQLException {
        //ps.setLong(1, this.id);
        ps.setString(1, this.name);
        ps.setInt(2, this.wCount);
    }

}