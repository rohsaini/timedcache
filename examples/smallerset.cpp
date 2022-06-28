#include "timedcache.h"

typedef struct data_xyz {
  int op;
  int key;
} data_xyz;

timedCache<uint32_t, data_xyz> *cachexyz = new timedCache<uint32_t, data_xyz>(4);

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

  int i = 0;

  long int timeKey = TIME_NOW;

  for (i = 1; i <= 40; i++)
  {
      data.op  = i;
      data.key = i*100;
      cachexyz->emplace(TIME_NOW, data);

      if (i % 5 == 0)
      {
        sleep(1);
      }
  }

  cout << "\nInitial Size : " << cachexyz->size();

  test_get_iter_expired_elem(timeKey);

  test_get_iter_expired_elem(111);

  test_remove_expired();

  cout << "\n\nSize after test_remove_expired(): " << cachexyz->size();

  auto iter = cachexyz->get_begin();
  timeKey = (*iter).first;

  get_elem_x_onwards(timeKey);

  get_elem_x_onwards(timeKey+2);

  cout << "\n\nLatest key is: " << cachexyz->get_latest_key() << "\n";

  sleep(2);
  test_remove_expired();

  cout << "\n\nSize after test_remove_expired(): " << cachexyz->size();

  if (cachexyz->empty())
  {
      cout << "\n\nCache is empty";
  }
  else
  {
      cout << "\n\nCache is not empty";
  }

  cout << "\n\nClearing the cache";
  cachexyz->clear();

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
