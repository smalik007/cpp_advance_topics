
#include <cstdint>
#include <iostream>

using namespace std;

#define IPU_PKT_HEADER 0xFF

void NET_UDP_send(const uint8_t* pkt, uint8_t len) {
  for (uint8_t i = 0; i < len; i++) {
    printf("%0x\t", pkt[i]);
  }
  cout << endl;

  uint64_t retrive_pkt = 0;
  for (size_t i = 3; i < sizeof(retrive_pkt) + 3; i++) {
    retrive_pkt |= (uint64_t)((uint64_t)pkt[i] << ((i - 3) * 8));
    // printf("%0x\t", pkt[i]);
    // printf("0x%016llX", temp);
    // cout << endl;
  }
  cout << endl;
  printf("0x%016llX", retrive_pkt);

  cout << endl;
}

void send_error_to_ipu(uint64_t error_flag) {
  uint8_t indx = 0;
  const uint8_t pkt_size = sizeof(uint8_t) * 3 + sizeof(error_flag);  // Header + msg_len + commandID + data
  uint8_t send_error_pkt[pkt_size] = {0};
  const uint8_t* p_error = (uint8_t*)&error_flag;

  send_error_pkt[indx++] = IPU_PKT_HEADER;
  send_error_pkt[indx++] = pkt_size - sizeof(IPU_PKT_HEADER) - sizeof(uint8_t); /* msg_len = size of complete buffer - header - lenbyte */
  send_error_pkt[indx++] = 'e';                                                 // Command ID

  uint8_t indx_offset = indx;
  for (; indx < sizeof(error_flag) + indx_offset; indx++) {
    send_error_pkt[indx] = p_error[indx - indx_offset];
  }
  printf("%d\n", pkt_size);
  NET_UDP_send(send_error_pkt, pkt_size);
}

int main() {
  uint64_t pkt = 0x0A0F0E0A0D0C0B0A;
  printf("0x%016llX", pkt);
  cout << endl;
  send_error_to_ipu(pkt);
  return 0;
}