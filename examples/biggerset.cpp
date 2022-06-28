#include "timedcache.h"
#include <chrono>

typedef struct data_xyz {
  uint32_t op;
  uint32_t key;
} data_xyz;

timedCache<uint32_t, data_xyz> *cachexyz = new timedCache<uint32_t, data_xyz>(60);

void test_get_iter_expired_elem(long int time1)
{
  if (cachexyz->get_elem_iter(time1) == cachexyz->get_end())
  {
      long int curr_time = TIME_NOW;
      cout << "\nExpired: " << time1 << " now: " << curr_time;
  }
}

void test_remove_expired()
{
  cout <<"\n\ntest_remove_expired called at " << TIME_NOW << "===>\n";
  cachexyz->remove_expired();
}

void get_elem_x_onwards(long int x)
{
  data_xyz data;

  cout <<"\n\n" << x << " onwards ===>\n";

  for (auto iter = cachexyz->get_elem_iter(x); iter != cachexyz->get_end() ; ++iter)
  {
      data = (*iter).second;
      cout << "\nkey: " << (*iter).first << " value: "<< data.op << " : " << data.key;
  }

}

int main()
{
  data_xyz data = {};

  uint32_t i = 0;

  long int timeKey = TIME_NOW;

  cout <<"\nTime : " << timeKey << "\n";

  for (i = 1; i <= 180000; i++)
  {
      data.op  = i;
      data.key = i*10;
      cachexyz->emplace(TIME_NOW, data);


      if (i % 3000 == 0)
      {
        sleep(1);
      }

  }

  cout << "\nInitial Size : " << cachexyz->size();


  cout <<"\nTime : " << TIME_NOW << "\n";

  sleep(20);

  cout <<"\nAfter sleep Time : " << TIME_NOW << "\n";

  test_remove_expired();

  cout << "\n\nSize after test_remove_expired(): " << cachexyz->size();

  cout <<"\nTime : " << TIME_NOW << "\n";

  auto iter = cachexyz->get_begin();
  timeKey = (*iter).first;
  cout <<"\nFirst elem: " << timeKey;

  if (cachexyz->empty())
  {
      cout << "\n\nCache is empty";
  }
  else
  {
      cout << "\n\nCache is not empty";
  }

  cout << "\n\n";

  return 0;
}
