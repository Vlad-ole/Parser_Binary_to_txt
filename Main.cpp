#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>

#include "ReadData.h"
#include "ReadData_CAEN.h"

using namespace std;

int main(int argc, char *argv[])
{
	clock_t t_total = clock();
	clock_t t_read_file = 0;
	clock_t t_calc_data = 0;
	clock_t t_tree_write = 0;
	clock_t t_f_tree_close = 0;
	clock_t t_tree_fill = 0;
	clock_t t_before;
	clock_t t_after;
	clock_t t_initialisation = 0;

	//-------------------------------------------------
	//For CAEN
	path_info PathInfo;
	//PathInfo.path_name = "D:\\Data_work\\170622_caen_raw\\event_x-ray_18_small_2\\";
	PathInfo.path_name = "D:\\data\\test\\test__events_per_file\\";
	PathInfo.path_name_txt = "D:\\data\\test\\test__events_per_file_txt\\";
	PathInfo.events_per_file = 10;

	vector<ch_info> ch_list;
	const int n_ch = 8;
	ch_list.resize(n_ch);
	for (int i = 0; i < n_ch; i++)
	{
		if (i < 8) ch_list[i].id = i;
		else ch_list[i].id = i + 24;
	}

	comm_info str_comm;
	str_comm.HORIZ_INTERVAL = 16;//ns per point;
	str_comm.WAVE_ARRAY_COUNT = 51;//number of points in one event
	//-------------------------------------------------

	//which raw files should be processed? 
	const int start_run_number = 1;
	const int stop_run_number = 1;
	const int n_runs = stop_run_number;
	cout << "n_runs = " << stop_run_number - start_run_number + 1 << endl;

	t_initialisation = clock() - t_total;
	for (int run_number = start_run_number; run_number <= stop_run_number; run_number++)
	{
		PathInfo.run_number = run_number;

		t_before = clock();
		ReadData_CAEN rdt(PathInfo, ch_list, str_comm);
		t_after = clock();
		t_read_file += t_after - t_before;
	}


	cout << "t_initialisation[ms] = " << (double)(t_initialisation) / (CLOCKS_PER_SEC) * 1000 << endl;
	cout << "t_read_file[ms] = " << (double)(t_read_file) / (CLOCKS_PER_SEC * n_runs) * 1000 << endl;
	cout << "t_calc_data[ms] = " << (double)(t_calc_data) / (CLOCKS_PER_SEC * n_runs) * 1000 << endl;
	cout << "t_tree_write[ms] = " << (double)(t_tree_write) / (CLOCKS_PER_SEC * n_runs) * 1000 << endl;
	cout << "t_f_tree_close[ms] = " << (double)(t_f_tree_close) / (CLOCKS_PER_SEC * n_runs) * 1000 << endl;
	cout << "t_tree_fill[ms] = " << (double)(t_tree_fill) / (CLOCKS_PER_SEC * n_runs) * 1000 << endl;
	cout << "t_total[ms] = " << (double)(clock() - t_total) / (CLOCKS_PER_SEC * n_runs) * 1000 << endl;

	cout << "all is ok" << endl;
	system("pause");
}