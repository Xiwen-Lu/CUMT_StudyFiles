package simpleHadoop;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.db.DBConfiguration;
import org.apache.hadoop.mapreduce.lib.db.DBOutputFormat;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.log4j.BasicConfigurator;

import java.io.IOException;
import java.util.StringTokenizer;

//标准WordCount，本地运行，读写本地文件
public class WordCountMysql {
    public static class TokenizerMapper
            extends Mapper<Object, Text, Text, IntWritable>{
        private final static IntWritable one = new IntWritable(1);
        private Text word = new Text();

        @Override
        public void map(Object key, Text value, Context context) throws IOException, InterruptedException {
            StringTokenizer itr = new StringTokenizer(value.toString());
            while (itr.hasMoreTokens()){
                word.set(itr.nextToken());
                context.write(word,one);
            }
        }
    }

    public static class IntSumReducer extends Reducer<Text,IntWritable,mysqlWritable,IntWritable>{
        private mysqlWritable result = new mysqlWritable();
        @Override
        protected void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
            int sum = 0;
            for (IntWritable val : values){
                sum += val.get();
            }
            result.setName(key.toString());
            result.setwCount(sum);

            context.write(result,null);

        }
    }

    public static void main(String[] args) throws IOException, ClassNotFoundException, InterruptedException {
        BasicConfigurator.configure();//自动快速地使用缺省log4j环境，建议放到main当中
        Configuration conf = new Configuration();
        String inpath = ".\\input\\input.txt";
//        DBConfiguration.configureDB(conf,"com.mysql.cj.jdbc.Driver"
//                ,"jdbc:mysql://127.0.0.1:3306/train_usergrant?serverTimezone=UTC"
//                ,"root","MySQL168681816");
        DBConfiguration.configureDB(conf,"org.postgresql.Driver"
                ,"jdbc:postgresql://127.0.0.1:5432/hadoop"
                ,"postgres","postgres");
        Job job = Job.getInstance(conf, WordCountMysql.class.getName());
        job.setJarByClass(WordCountMysql.class);

        job.setMaxMapAttempts(3);
        job.setInputFormatClass(TextInputFormat.class);
        job.setOutputFormatClass(DBOutputFormat.class);

        job.setMapperClass(TokenizerMapper.class);
        job.setReducerClass(IntSumReducer.class);

        job.setMapOutputKeyClass(Text.class);
        job.setMapOutputValueClass(IntWritable.class);
        job.setOutputKeyClass(mysqlWritable.class);
        job.setOutputValueClass(IntWritable.class);

        FileInputFormat.addInputPath(job,new Path(inpath));
//        DBOutputFormat.setOutput(job,"MapReduceTest","单词","count");
        //由此可见这里给出输出表的列字段个数也是可以的
        DBOutputFormat.setOutput(job,"MapReduceTest",2);

        int num = job.waitForCompletion(true)?0:1;
        System.exit(num);
    }
}

