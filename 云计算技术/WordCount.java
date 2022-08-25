package simpleHadoop;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.log4j.BasicConfigurator;
import java.io.IOException;
import java.util.StringTokenizer;

//标准WordCount，本地运行，读写本地文件
public class WordCount{
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

    public static class IntSumReducer extends Reducer<Text,IntWritable,Text,IntWritable>{
        private IntWritable result = new IntWritable();

        @Override
        protected void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
            int sum = 0;
            for (IntWritable val : values){
                sum += val.get();
            }
            result.set(sum);
            context.write(key,result);

        }
    }

    public static void main(String[] args) throws IOException, ClassNotFoundException, InterruptedException {
        BasicConfigurator.configure();//自动快速地使用缺省log4j环境，建议放到main当中

        Configuration conf = new Configuration();
        //设置通过域名访问datanode
        conf.set("dfs.client.use.datanode.hostname", "true");

        String[] argss = {".\\input\\input.txt",".\\output\\simple"};
//        String[] argss = {"hdfs://123.207.227.230:9000/lxw/input/input.txt","hdfs://123.207.227.230:9000/lxw/output"};
        String inpath = argss[0];
        String outpath = argss[1];
        Job job = Job.getInstance(new Configuration(), WordCount.class.getName());
        job.setJarByClass(WordCount.class);

        job.setMaxMapAttempts(3);
        job.setInputFormatClass(TextInputFormat.class);
        job.setOutputFormatClass(TextOutputFormat.class);

        job.setMapperClass(TokenizerMapper.class);
        job.setReducerClass(IntSumReducer.class);

        job.setMapOutputKeyClass(Text.class);
        job.setMapOutputValueClass(IntWritable.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(IntWritable.class);

        FileInputFormat.addInputPath(job,new Path(inpath));
        FileOutputFormat.setOutputPath(job,new Path(outpath));
        int num = job.waitForCompletion(true)?0:1;
        System.exit(num);
    }
}

