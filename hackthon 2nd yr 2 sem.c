#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRANS 100
#define HASH_LEN 65
#define ADDRESS_LEN 43

typedef struct {
    char tx_hash[HASH_LEN];
    char sender[ADDRESS_LEN];
    char receiver[ADDRESS_LEN];
    double amount;
    char timestamp[30];
} Transaction;

typedef struct {
    Transaction transactions[MAX_TRANS];
    int count;
} TransactionList;

TransactionList fetch_transactions(const char *wallet_id) {
    TransactionList tx_list;
    tx_list.count = 0;
    if (strcmp(wallet_id, "walletX") == 0) {
        strcpy(tx_list.transactions[0].tx_hash, "abc123");
        strcpy(tx_list.transactions[0].sender, "walletX");
        strcpy(tx_list.transactions[0].receiver, "walletY");
        tx_list.transactions[0].amount = 10.5;
        strcpy(tx_list.transactions[0].timestamp, "2024-04-01T10:00:00Z");
        tx_list.count = 1;
    } else if (strcmp(wallet_id, "walletY") == 0) {
        strcpy(tx_list.transactions[0].tx_hash, "def456");
        strcpy(tx_list.transactions[0].sender, "walletY");
        strcpy(tx_list.transactions[0].receiver, "walletZ");
        tx_list.transactions[0].amount = 5.2;
        strcpy(tx_list.transactions[0].timestamp, "2024-04-01T11:00:00Z");
        tx_list.count = 1;
    } else if (strcmp(wallet_id, "walletZ") == 0) {
        strcpy(tx_list.transactions[0].tx_hash, "ghi789");
        strcpy(tx_list.transactions[0].sender, "walletZ");
        strcpy(tx_list.transactions[0].receiver, "walletFinal");
        tx_list.transactions[0].amount = 3.1;
        strcpy(tx_list.transactions[0].timestamp, "2024-04-01T12:00:00Z");
        tx_list.count = 1;
    }
    return tx_list;
}

void trace_funds(const char *start_wallet) {
    TransactionList tx_list = fetch_transactions(start_wallet);
    int i;
    for (i = 0; i < tx_list.count; i++) {
        if (strcmp(tx_list.transactions[i].sender, start_wallet) == 0) {
            printf("Hash: %s\n", tx_list.transactions[i].tx_hash);
            printf("Receiver: %s\n", tx_list.transactions[i].receiver);
            printf("Amount: %.2f\n", tx_list.transactions[i].amount);
            printf("Timestamp: %s\n", tx_list.transactions[i].timestamp);
            trace_funds(tx_list.transactions[i].receiver);
        }
    }
}

int main() {

	char input_wallet[ADDRESS_LEN];
    printf("Enter starting wallet address: ");
    fgets(input_wallet, sizeof(input_wallet), stdin);
    input_wallet[strcspn(input_wallet, "\n")] = 0;
    trace_funds(input_wallet);
    return 0;
}
