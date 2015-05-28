fid=fopen('SC2_demo_all_times_50000_8BUF_optimised_release.txt');
data=fscanf(fid,'%d',[6 50000])';

% fid=fopen('SC2_demo_all_times_optimized_50000_2BUF_optimised_release.txt');
% data=fscanf(fid,'%d',[5 50000])';

% % fid=fopen('SC2_demo_all_times_50000.txt');
% % data=fscanf(fid,'%d',[5 50000])';

milliseconds=data(:,2)*60*60*1000+data(:,3)*60*1000+data(:,4)*1000+data(:,5);
max_diff=max(diff(milliseconds));
min_diff=min(diff(milliseconds));

interval=(min_diff:max_diff)';

vals=histc(diff(milliseconds),interval);

bar(interval,vals)

[interval vals]
[interval(vals>0) vals(vals>0)]

std(reshape(data(:,6),[8 50000/8]),[],2)




