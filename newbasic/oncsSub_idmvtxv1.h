#ifndef __ONCSSUB_IDMVTXV1_H__
#define __ONCSSUB_IDMVTXV1_H__

#include "oncsSubevent.h"
#include <vector>

using namespace std;

#ifndef __CINT__
class WINDOWSEXPORT oncsSub_idmvtxv1 : public  oncsSubevent_w4 {
#else
    class  oncsSub_idmvtxv1 : public  oncsSubevent_w4 {
#endif

#define MAXRUID       1
#define RUHEADER      0xE0
#define RUTRAILER     0xF0
#define MAXRUCHN      28
#define MAXCHIPID     9
        public:
            oncsSub_idmvtxv1( subevtdata_ptr);
            ~oncsSub_idmvtxv1();

            int    iValue(const int ruid, const char *what);
            int    iValue(const int ruid);
            int    iValue(const int ruid, const int ruchn, const char *what);
            int    iValue(const int ruid, const int ruchn);
            int    iValue(const int ruid, const int ruchn, const int i);

            //max 24 RUs
            //max 28 ruchn/RU (each is a chip)
            //ruid, what -> RU info
            //ruid -> chn mask
            //ruid, ruchn, what -> chip info
            //ruid, ruchn -> chip hit count
            //ruid, ruchn, i -> hit info
            //hit info: 32 bits, 1024x512 -> 9 bits row, 10 bits col

            void  dump ( OSTREAM& os = COUT) ;
            void  gdump ( const int how=EVT_HEXADECIMAL, OSTREAM& os = COUT) const; // add this to override the generic gdump

            unsigned int encode_hit(unsigned short row, unsigned short col) const;
            unsigned short decode_row(unsigned int hit) const;
            unsigned short decode_col(unsigned int hit) const;

        protected:
            int *decode ();

            int _is_decoded;

            int _highest_ruid;
            int _ruchn_mask[MAXRUID+1];

            vector<int> _hit_vectors[MAXRUID+1][MAXRUCHN+1];

            int _unexpected_felix_counter;
            int _bad_ruid;
            int _bad_ruchns;
            int _bad_chipids;
            //int _highest_row_overall;
            //int _highest_chip;
            int _excess_data_bytes;
            int _chip_id[MAXRUID+1][MAXRUCHN+1];
            //int _highest_region[MAXRUCHN+1];
            int _unexpected_bytes[MAXRUID+1][MAXRUCHN+1];
            int _bunchcounter[MAXRUID+1][MAXRUCHN+1];
            bool _header_found[MAXRUID+1][MAXRUCHN+1];
            bool _trailer_found[MAXRUID+1][MAXRUCHN+1];
            int _readout_flags[MAXRUID+1][MAXRUCHN+1];

            int decode_thebit(int the_row, int encoder_id, int address) const; //helper function to decode the column number
            void print_stuff(OSTREAM& out, unsigned int data, int width, int shift, bool blank = false) const;
    };



#endif /* __ONCSSUB_IDMVTXV1_H__ */
