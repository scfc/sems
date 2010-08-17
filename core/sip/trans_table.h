#ifndef _trans_table_h_
#define _trans_table_h_

#include "hash_table.h"

#define H_TABLE_POWER   10
#define H_TABLE_ENTRIES (1<<H_TABLE_POWER)

class trans_bucket: 
    public ht_bucket<sip_trans>
{
public:
    typedef ht_bucket<sip_trans>::value_list trans_list;

    /**
     * Kept public to allow for static construction.
     * !!! DO CREATE ANY BUCKETS ON YOUR OWN !!!
     */
    // trans_bucket();
    trans_bucket(unsigned long id);
    ~trans_bucket();
    
    // Match a request to UAS transactions
    // in this bucket
    sip_trans* match_request(sip_msg* msg);

    // Match a reply to UAC transactions
    // in this bucket
    sip_trans* match_reply(sip_msg* msg);

    sip_trans* add_trans(sip_msg* msg, int ttype);

    // /**
    //  * Remove a transaction from this bucket,
    //  * if it was still present.
    //  */
    // void remove_trans(sip_trans* t);

private:
    sip_trans* match_200_ack(sip_trans* t,sip_msg* msg);
    sip_trans* match_1xx_prack(sip_trans* t,sip_msg* msg);
};

trans_bucket* get_trans_bucket(const cstring& callid, const cstring& cseq_num);
trans_bucket* get_trans_bucket(unsigned int h);

unsigned int hash(const cstring& ci, const cstring& cs);


#define BRANCH_BUF_LEN 8

void compute_branch(char* branch/*[BRANCH_BUF_LEN]*/, 
		    const cstring& callid, const cstring& cseq);

#define SL_TOTAG_LEN BRANCH_BUF_LEN

void compute_sl_to_tag(char* to_tag/*[SL_TOTAG_LEN]*/, sip_msg* msg);

void dumps_transactions();


#endif