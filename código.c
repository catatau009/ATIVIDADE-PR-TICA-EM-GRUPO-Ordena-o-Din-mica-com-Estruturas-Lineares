#include <stdio.h>
#include <stdlib.h>

// Variáveis globais para rastrear comparações e trocas/movimentações
int comparacoes = 0;
int trocas = 0;

// Função auxiliar para trocar dois elementos e contar a troca
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    trocas++;
}

// Função para zerar os contadores antes de cada execução de ordenação
void reset_counters() {
    comparacoes = 0;
    trocas = 0;
}

// 1. Bubble Sort
void bubbleSort(int arr[], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if(arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

// 2. Selection Sort
void selectionSort(int arr[], int n) {
    for(int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for(int j = i + 1; j < n; j++) {
            comparacoes++;
            if(arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if(min_idx != i) {
            swap(&arr[min_idx], &arr[i]);
        }
    }
}

// 3. Insertion Sort
void insertionSort(int arr[], int n) {
    for(int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while(j >= 0) {
            comparacoes++;
            if(arr[j] > key) {
                arr[j + 1] = arr[j];
                trocas++; // Contabilizado como troca/movimentação
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
        trocas++; // Posicionamento final da chave
    }
}

// 4. Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        comparacoes++;
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 5. Merge Sort
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        comparacoes++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        trocas++; // Contabilizado como atribuição/movimentação
        k++;
    }
    
    while (i < n1) { arr[k] = L[i]; i++; k++; trocas++; }
    while (j < n2) { arr[k] = R[j]; j++; k++; trocas++; }
    
    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// 6. Shell Sort
void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap; j -= gap) {
                comparacoes++;
                if(arr[j - gap] > temp) {
                    arr[j] = arr[j - gap];
                    trocas++;
                } else {
                    break;
                }
            }
            arr[j] = temp;
            trocas++;
        }
    }
}

// 7. Heap Sort
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        comparacoes++;
        if(arr[left] > arr[largest]) largest = left;
    }

    if (right < n) {
        comparacoes++;
        if(arr[right] > arr[largest]) largest = right;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// Função para imprimir o vetor
void printArray(int arr[], int n) {
    printf("Estrutura atual: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int escolha, quantidade;

    printf("Escolha o algoritmo:\n");
    printf("1 - Bubble Sort\n");
    printf("2 - Selection Sort\n");
    printf("3 - Insertion Sort\n");
    printf("4 - Quick Sort\n");
    printf("5 - Merge Sort\n");
    printf("6 - Shell Sort\n");
    printf("7 - Heap Sort\n\n");
    
    printf("Opção: ");
    if (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > 7) {
        printf("Opção inválida!\n");
        return 1;
    }

    printf("\nQuantos valores deseja inserir? ");
    if (scanf("%d", &quantidade) != 1 || quantidade <= 0) {
        printf("Quantidade inválida!\n");
        return 1;
    }

    // Aloca memória para o vetor principal com a capacidade máxima
    int *vetor = (int *)malloc(quantidade * sizeof(int));
    if (vetor == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    printf("\n");

    // Loop de inserção dinâmica
    for (int i = 0; i < quantidade; i++) {
        int valor;
        printf("Digite o valor: ");
        scanf("%d", &valor);

        // Insere o novo valor no final da porção preenchida do vetor
        vetor[i] = valor;
        int tamanho_atual = i + 1;

        // Reseta os contadores para medir a performance da ordenação DESTA rodada
        reset_counters();

        // Só faz sentido ordenar se houver mais de 1 elemento
        if (tamanho_atual > 1) {
            switch(escolha) {
                case 1: bubbleSort(vetor, tamanho_atual); break;
                case 2: selectionSort(vetor, tamanho_atual); break;
                case 3: insertionSort(vetor, tamanho_atual); break;
                case 4: quickSort(vetor, 0, tamanho_atual - 1); break;
                case 5: mergeSort(vetor, 0, tamanho_atual - 1); break;
                case 6: shellSort(vetor, tamanho_atual); break;
                case 7: heapSort(vetor, tamanho_atual); break;
            }
        }

        // Mostra a estrutura do vetor após o algoritmo agir
        printArray(vetor, tamanho_atual);
        
        // Exibe o número de comparações e trocas feitas na etapa
        printf("Comparações: %d | Trocas (movimentações): %d\n\n", comparacoes, trocas);
    }

    free(vetor);
    printf("Fim do programa.\n");
    return 0;
}
