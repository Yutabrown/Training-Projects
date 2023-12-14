class CoinConverter:
    def __init__(self):
        self.coins = {"euro": 5.36, "usd": 4.96} # Os valores foram definidos com base em uma pesquisa realizada em 12/12/2023 às 21:41

def convert(origin_coin, destiny_coin):
    final_coin = origin_coin * destiny_coin 
    print(f"{origin_coin} foi convertido para {final_coin:.2f} usando {destiny_coin} como base") #O valor final a ser impresso é calculado multiplicando o input do usuário pela forma de conversão escolhida por ele.
        
def main():
    coin_converter = CoinConverter()
    
    valid_destiny = False

    while not valid_destiny:
        print("Insira a forma de conversão (Euro, Real, USD): ", end="")
        destiny = input().lower()

        if destiny in coin_converter.coins:
                valid_destiny = True
                print("Moeda de conversão válida.")

        else:
            print("Insira uma forma de conversão válida.")

    destiny_coin = coin_converter.coins[destiny]

    print("Insira o valor que você deseja converter: ", end="")
    origin_coin = float(input())
    
    convert(origin_coin, destiny_coin)
    
if __name__ == "__main__":
    main()
