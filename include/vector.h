/*! @file vector.h
    @brief estrutura de dado vetor.
*/

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef CSTDLIB
#define CSTDLIB
#include <cstdlib>
#endif

using namespace std;

template < typename T >
class vector {
    public:
        using size_type = unsigned long;  /*!< @var usado por exemplo como um indice (int) */
        typedef std::ptrdiff_t difference_type;  /*!< @var diferença entre dois ponteiros */
        typedef T value_type;  /*!< @var tipo de dado armazenado */
        typedef T* pointer;  /*!< @var ponteiro para o tipo de dado */
        typedef T& reference; /*!< @var referência para o tipo de dado */
        typedef const T& const_reference;  /*!< @varreferência constante para o tipo de dado */
       
        class MyIterator{
            public:
                
                /**
                * @brief Contruttor sem argumentos, data = nullptr
                */
                MyIterator(){
                    this->current = nullptr;
                }

                /**
                * @brief Contruttor com ponteiro
                * @param  p ponteiro a ser atribuido a current
                */
                MyIterator(pointer p){
                    this->current = p;
                }
                
                /**
                * @brief atribuição a um iterator
                * @param  m iterator que seu current será igual ao current da classe
                */
                MyIterator& operator=(const MyIterator& m){
                    this->current = m.current;
                    return *this;
                }


                /**
                * @brief atribuição a um iterator
                * @param  m const iterator que seu current será igual ao current da classe
                */
                MyIterator(const MyIterator& m){
                    this->current = m.current;
                }


                /**
                * @brief valor do iterator atual
                * @return referencia para o valor do current
                */
                reference operator* ( ) const{
                    return *current;
                }

                /**
                * @brief ponteiro do current
                * @return um ponteiro para a variavel current
                */
                pointer operator ->(void) const {
                    assert( current != nullptr );
                    return current; 
                }

                /**
                * @brief current aumenta uma vez o tamanho do seu tipo
                * @return referencia para um proximo iterator
                */
                MyIterator& operator++( ){
                    return MyIterator(++current);
                } 

                /**
                * @brief current aumenta uma vez o tamanho do seu tipo, após a execução da linha atual
                * @return referencia para um proximo iterator
                */
                MyIterator operator++ (int){
                    return MyIterator(current++);
                }

                /**
                * @brief current diminui uma vez o tamanho do seu tipo
                * @return referencia para iterator anterior
                */
                MyIterator& operator-- (){
                    return MyIterator(--current);
                }

                /**
                * @brief current diminui uma vez o tamanho do seu tipo, após a execução da linha atual
                * @return referencia para iterator anterior
                */
                MyIterator& operator-- (int){
                    return MyIterator(current--);
                }

                /**
                * @brief concatena dois iterators
                * @param  d iterator
                * @param  m iterator
                * @return retorna um iterador com o current igual a soma de dois iterators
                */
                friend MyIterator operator+( difference_type d, MyIterator m){
                    return MyIterator(m.current+d);
                }

                /**
                * @brief concatena dois iterators
                * @param  m iterator
                * @param  d iterator
                * @return retorna um iterador com o current igual a soma de dois iterators
                */
                friend MyIterator operator+(MyIterator m, difference_type d){
                    return MyIterator(m.current+d);
                }

                /**
                * @brief a diferença entre dois interators
                * @param  d iterator
                * @param  m iterator
                * @return retorna um iterador com o current igual a diferença de dois iterators
                */
                friend MyIterator operator-( difference_type d, MyIterator m){
                    return MyIterator(m.current-d);
                }

                /**
                * @brief a diferença entre dois interators
                * @param  d iterator
                * @param  m iterator
                * @return retorna um iterador com o current igual a diferença de dois iterators
                */
                friend MyIterator operator-(MyIterator m, difference_type d){
                    return MyIterator(m.current-d);
                }

                /**
                * @brief a diferença entre dois interators (int)
                * @return um inteiro que é a diferença entres os currents
                */
                friend int operator-(MyIterator m1, MyIterator m2){
                    return abs(m2.current-m1.current);
                }

                /**
                * @brief compara os dois current, verifica se são iguais
                * @param  m iterator
                * @return a senteça da igualdade de dois currents
                */
                bool operator== ( const MyIterator& m) const{
                    return m.current == current;
                }

                /**
                * @brief compara os dois current, verifica se são diferentes
                * @param  m iterator
                * @return a senteça da diferença de dois currents
                */
                bool operator!= ( const MyIterator& m) const{
                    return m.current != current;
                }

            private:
                T * current; // current é o valor que o interator tenta esconder do usuário finas

        };

        class ConstMyIterator{
                
                /**
                * @brief Contruttor sem argumentos, data = nullptr
                */
                ConstMyIterator(){
                    this->current = nullptr;
                }

                /**
                * @brief Contruttor com ponteiro
                * @param  p ponteiro a ser atribuido a current
                */
                ConstMyIterator(pointer p){
                    this->current = p;
                }

                /**
                * @brief atribuição a um iterator
                * @param  m const iterator que seu current será igual ao current da classe
                */
                ConstMyIterator(const ConstMyIterator& m){
                    this->current = m.current;
                }

                /**
                * @brief valor do iterator atual
                * @return referencia para o valor do current
                */
                reference operator* ( ) const{
                    return *current;
                }

                /**
                * @brief ponteiro do current
                * @return um ponteiro para a variavel current
                */
                pointer operator ->(void) const {
                    assert( current != nullptr );
                    return current; 
                }

                /**
                * @brief compara os dois const current, verifica se são iguais
                * @param  m const iterator
                * @return a senteça da igualdade de dois currents
                */
                bool operator== ( const ConstMyIterator& m) const{
                    return m.current == current;
                }

                /**
                * @brief compara os dois const current, verifica se são diferentes
                * @param  m const iterator
                * @return a senteça da diferença de dois currents
                */
                bool operator!= ( const ConstMyIterator& m) const{
                    return m.current != current;
                }

                friend int operator-(MyIterator m1, MyIterator m2){
                    return abs(m2.current-m1.current);
                }

            private:
                T * current;
        }; 

        /** @brief verifica se a o tamanho atual do vector é igual a capacidade, se sim aloca mais memória */
        void isCheia(){
        	if ( size_now == capacity_now ){
                reserve( ( capacity_now == 0 ) ? 1 : (2 * capacity_now) );
            }
        }

        /**
        * @brief verifica se a o tamanho atual do vector é igual a capacidade, se sim aloca mais memória 
        * @param t valor que na verificação será soma ao tamanho do vector
        */
        void isCheia(int t){
        	if ( size_now == capacity_now || size_now+t >= capacity_now){
                reserve( ( capacity_now == 0 ) ? 1 : (2 * capacity_now) );
            }
        }

        // [I] membros especiais

        /**
        * @brief construtor iniciando com um tamanho informado 
        * @param count tamanho da capacidade do vector
        */
        explicit vector( size_t count=0 ) :
            storage{ new T[ 2*count ] },
            size_now { count },
            capacity_now { 2*count }
        { /* empty */ }


        /**
        * @brief construtor iniciando com os mesmos valores de outro vector
        * @param source vector a ser copiado
        */
        vector( const vector& source )
            : size_now { source.size },
            capacity_now { source.capacity }
        {
             // [1] Alocar o espaço de dados.
             storage = new T[ capacity ];
             // [2] Copiar os elementos do source para o atual (this).
             std::copy( &source.storage[0], &source.storage[size], storage );
        }

        /**
        * @brief construtor iniciando com os mesmos valores de outro vector
        * @param source vector a ser copiado
        */
        vector( vector && s)
            : size_now { s.size_now },
            capacity_now { s.capacity_now }
        {
             // [1] Alocar o espaço de dados.
             storage = new T[ capacity ];
             // [2] Copiar os elementos do source para o atual (this).
             std::copy( &s.storage[0], &s.storage[size_now], storage );
        }

        /**
        * @brief construtor que iguala o vector a uma lista, ex: {1, 2, 3}
        * @param l lista a ser copiada 
        */
        vector( std::initializer_list<T> l)
            : size_now { l.size() },
            capacity_now { l.size() }
        {
            storage = new T[capacity_now];
            std::copy( l.begin(), l.end(), storage);
        }

        /**
        * @brief iguala um vector a outro vector
        * @param s vector a ser copiado
        * @return uma referencia para vector
        */
        vector& operator=( vector && s) {
             capacity = s.capacity;
             size_now = s.size_now;
             // [1] Alocar o espaço de dados.
             storage = new T[ capacity ];
             // [2] Copiar os elementos do source para o atual (this).
             std::copy( &s.storage[0], &s.storage[size_now], storage );
        }

        /**
        * @brief iguala um vector a um const vector
        * @param s vector constante a ser copiado
        * @return uma referencia para vector
        */
        vector& operator=( const vector& rhs ){
            size_now = rhs.size_now;
            capacity = rhs.capacity;

            // [1] Alocar o espaço de dados.
            storage = new T[ capacity ];
            // [2] Copiar os elementos do source para o atual (this).
            std::copy( &rhs.storage[0], &rhs.storage[size_now], storage );

            return *this;
        }

        /**
        * @brief destrutor do vector, apaga o ponteiro que guarda os dados
        */
        ~vector(){
            delete [] storage;
        }

        // fim [I]

        //---------------------------------------------------------------------------------------------------

        //=== [II] ITERATORS
       
        /**
        * @brief iterator do começo do vector
        * @return um iterator para o começo do vector
        */
        MyIterator begin(void){
            return MyIterator(storage);
        }

        /**
        * @brief iterator do fim do vector
        * @return um iterator para o fim do vector
        */
        MyIterator end(void){
            return MyIterator(storage+size_now);
        }

        /**
        * @brief const iterator do começo do vector
        * @return um const iterator para o começo do vector
        */
        ConstMyIterator cbegin(void){
            return ConstMyIterator(storage);
        }

        /**
        * @brief const iterator do fim do vector
        * @return um const iterator para o fim do vector
        */
        ConstMyIterator cend(void){
            return ConstMyIterator(storage+size_now);
        }
        
        // fim [II]

        //---------------------------------------------------------------------------------------------------

        // [III] Capacity

        /**
        * @brief tamanho do vector
        * @return quantidade de elementos do vector
        */
        size_type size(void) const{
            return (size_type) size_now;
        }

        /**
        * @brief capacidade de elementos atual do vector
        * @return capacidade atual vector
        */
        size_type capacity( void ) const{
            return (size_type) capacity_now;
        }

        /**
        * @brief verifica se o vector possui elementos
        * @return true caso o vector estaja vazio, e false caso contrario
        */
        bool empty( void ) const{
            return (size_now == 0);
        }
        //fim [III]

        //---------------------------------------------------------------------------------------------------

        // [IV] Modifiers

        /**
        * @brief o vector está com seu número de elementos vazio, ou seja não possui elementos
        */
        void clear(void){
            this->size_now = 0;
        }

        /**
        * @brief adiociona um elemento do começo do vector
        * @param value valor a ser inserido
        */
        void push_front( const T & value ){
            isCheia();
            //copiando os elmentos uma posição a frente
            std::copy( &storage[0], &storage[size_now], storage  );

            // Inserir normalmente.
            *begin() = value;
            size_now++;
        }


        /**
        * @brief adiociona um elemento do fim do vector
        * @param value valor a ser inserido
        */
        void push_back( const T & value ){
            isCheia();
            // Inserir normalmente.
            storage[size_now++] = value;
            //*begin() = value;
        }

        /**
        * @brief remove um elemento do fim do vector
        * @param value valor a ser removido
        */
        void pop_back(void){
            size_now--;
        }

        /**
        * @brief remove um elemento do começo do vector
        * @param value valor a ser removido
        */
        void pop_front(void){
            //copiando os elmentos uma posição para trás
            std::copy( &storage[1], &storage[size_now], storage );
            size_now--;
        }

        /**
        * @brief aumenta a capacidade do vector, sem perder seus dados
        * @param new_cap valor a nova capacidade
        */
        void reserve( size_t new_cap ){
            // Se a capacidade nova < capacidade atual, não faço nada.
            if ( new_cap <= capacity_now ) return;

            // Passo 1: alocar nova memória com tamanho solicitado.
            T * temp = new T[ new_cap ];

            // Passo 2: copiar os dados da memória antiga para a nova.
            std::copy( &storage[0], &storage[size_now],  temp );
            //std::copy( begin(), end(), temp );

            // Passo 3: Liberar a memória antiga.
            delete[] storage;

            // Passo 4: Redirecionar ponteiro para a nova (maior) memória.
            storage = temp;

            // Passo 5: Atualizações internas.
            capacity_now = new_cap;
        }

        /**
        * @brief insere um dado, numa posição especifica
        * @param it local onde será o novo valor
        * @param t novo dado que será inserido
        * @return um iterator para o local onde o dado foi inserido
        */
        MyIterator insert(MyIterator it , const T& r){
            int dif = it-begin(); //pode ser alocado um novo vetor. perda da diferença para o it
            isCheia();
            std::copy( &storage[dif], &storage[size_now],  &storage[dif+1] );
            size_now++;
            storage[dif] = r;
 			
            return MyIterator(storage+dif);
        }

        /**
        * @brief insere uma de dados, apartir de posição especifica
        * @param it local apartir de onde os dados vão ser inseridos
        * @param first começo da seuqncia de dados
        * @param last o posterior ao fim da seuqncia de dados
        * @return um iterator para o local onde o dado foi inserido
        */
        template <typename InputIterator>
        MyIterator insert(MyIterator it, InputIterator first, InputIterator last){
        	int size_list_temp = last-first;
        	int dif = it-begin();
        	isCheia(size_list_temp);

        	std::copy( &storage[dif], &storage[size_now],  &storage[dif+size_list_temp] ); // deslocando elementos size_list_temp 
        	
        	for (int i = 0; i < size_list_temp; ++i){
        		storage[dif+i] = *first;
        		first++;
        	}

        	size_now += size_list_temp;
        	return MyIterator(storage+dif);
        }

        /**
        * @brief insere uma de dados, apartir de uma lista, ex {1, 2, 3}
        * @param it local apartir de onde os dados vão ser inseridos
        * @param list lista de dados a serem inseridos
        * @return um iterator para o local onde o dado foi inserido
        */
        MyIterator insert(MyIterator it,const std::initializer_list<T>& list){
        	int dif = it-begin();
        	isCheia(list.size());
        	
        	std::copy( &storage[dif], &storage[size_now],  &storage[dif+list.size()] ); // deslocando elementos list.size

        	insert(MyIterator(&storage[dif]), list.begin(), list.end());
        	
        	return MyIterator(&storage[dif]);
        }

        /** @brief iguala a capacidade do vector a seu tamanho de elementos. */
        void shrink_to_fit(void){
            capacity_now = size_now;
        }

        /** @brief recria o vector para ser uma 'lista' de tamanho 'qtd', em que todos os dados são igual a 'value'
		* @param qtd quantidade de dados do novo vector
		* @param value valor a ser copiado para todos os dados do vector
        */
        void assign(int qtd, const T & value ){
            if ( capacity_now < qtd){
                reserve(qtd);
            }
            
            for (int i = 0; i < qtd; i++){
                storage[i] = value;
            }

            size_now = qtd;
        }

        /** @brief recria o vector para seus dados serem iguais a uma lista fornecida
		* @param list lista a ser igual a os dados do vector
        */
        void assign(const std::initializer_list<T>& list){
            if ( capacity_now < list.size()){
                reserve(list.size());
            }
            
            std::copy( list.begin(), list.end(), storage);

            size_now = list.size();
        }


        /** @brief recria o vector apartir de dois InputIterator
		* @param first começo da lista a ser copiada
		* @param last sucessor do fim da lista a ser copiada
        */
        template <typename InputIterator >
        void assign(InputIterator first, InputIterator last ){
            int size_list = last-first;

            if ( capacity_now < size_list){
                reserve(size_list);
            }
            size_now = size_list;
            
            size_list = 0;
            while(first != last){
                storage[size_list++] = *first++;
            }
            
        }

		/**
        * @brief apaga um dado do vector
        * @param it iterator a ser apagado
        * @return um iterator para o local onde o dado foi removido
        */
        MyIterator erase(MyIterator it){
            int size_temp = it - begin();
            
            if(size_temp == capacity_now){
                pop_back();
                return end();
            }else if(size_temp == 0){
                pop_front();
                return begin();
            }else{
                std::copy( storage+(size_temp+1), storage+size_now, storage+size_temp);
            	return MyIterator(storage+size_temp);
            }
        }
        // fim [IV]

        //---------------------------------------------------------------------------------------------------

        // [V] Element access

        /**
        * @brief ultimo elemento do vector (const)
        * @return uma referencia constante para o ultimo elemento do vector
        */
        const_reference back(void) const{
            return ConstMyIterator(storage+size_now-1);
        }

        /**
        * @brief ultimo elemento do vector
        * @return uma referencia para o ultimo elemento do vector
        */
        reference back(void){
            return MyIterator(storage+size_now-1);
        }

        /**
        * @brief primeiro elemento do vector (const)
        * @return uma referencia constante para o primeiro elemento do vector
        */
        const_reference front(void) const{
            return ConstMyIterator(storage);
        }

        /**
        * @brief primeiro elemento do vector 
        * @return uma referencia para o primeiro elemento do vector
        */
        reference front(void){
            return MyIterator(storage);
        }

        /**
        * @brief referencia constante para um dado num indice
        * @param indice posicao a ser buscada
        * @return uma referencia constante para o dado da posição 'indice' elemento do vector
        */
        const_reference operator[](size_type indice) const{
            return storage[indice];
        }

        /**
        * @brief referencia para um dado num indice
        * @param indice posicao a ser buscada
        * @return uma referencia para o dado da posição 'indice' elemento do vector
        */
        reference operator[](size_type indice){
            return storage[indice];
        }

        /**
        * @brief referencia constante para um dado num indice
        * @param indice posicao a ser buscada
        * @return uma referencia constante para o dado da posição 'indice' elemento do vector
        */
        const_reference at( size_type indice) const{
            if(indice >= 0 && indice < size_now){
                return storage[indice];
            }
        }

        /**
        * @brief referencia para um dado num indice
        * @param indice posicao a ser buscada
        * @return uma referencia para o dado da posição 'indice' elemento do vector
        */
        reference at( size_type indice){
            if(indice >= 0 && indice < size_now){
                return storage[indice];
            }
        }

        /**
        * @brief referencia para os dados
        * @return referencia dos dados armazenados
        */
        reference data(void){
            return storage;
        }

        /**
        * @brief referencia constante para os dados
        * @return referencia constante dos dados armazenados
        */
        const_reference data(void) const{
            return storage;
        }

        // fim [V]
   		
   		// [VII] Friend functions.
        /**
        * @brief mostra os dados do vector
        * @param os onde os dados vão ser inseridos
        * @param v vector a ser mostrado
        * @return um ostream a ser mostrado
        */
        friend ostream& operator<<(ostream& os, const vector<value_type>& v){
        	os << "[ ";
        	for (int i = 0; i < v.size(); ++i){
        		os << v[i];
        	}
        	os << "]";
        	return os;
        }
   		// fim [VII]
        //---------------------------------------------------------------------------------------------------

    private:
        T * storage; //!< Area de armazenamento.
        size_t size_now; //!< Número de elementos atualmente no vector.
        size_t capacity_now; //!< Capacidade máxima (atual) do vector.
};