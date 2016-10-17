floyd() {
	for (int i = 0; i < n; ++i) {  // 1 + n+1 + n = 2n + 2
		for (int j = 0; i < n; ++j) {  // (1 + n+1 + n) * n = 2n² + 2n
			A[i][j] = D[i][j];  // 1 * n * n = n²
			R[i][j] = 0;  // 1 * n * n = n²
		}
	}
	for (int i = 0; i < n; ++i) {  // 1 + n + 1 + n = 2n + 2
		A[i][i] = 0;  // 1 * n = n
	}
	for (int k = 0; k < n; ++k) {  // 1 + n+1 + n = 2n+2
		for (int i = 0; i < n; ++i) {  // (1 + n+1 + n) * n = 2n²+2n
			for (int j = 0; j < n; ++j) {  // ((1 + n+1 +n) * n) * n = 2n³+2n²
				if (A[i][k] + A[k][j] < A[i][j]) {  // (1 + 1) * n³ = 2n³
					A[i][j] = A[i][k] + A[k][j];  // (1 + 1) * n³ = 2n³
					R[i][j] = k;  // 1 * n³ = n³
				}
			}
		}
	}
}

/*
 (2n+2) + (2n²+2n) + (n²) + (n²) + (2n+2) + (n) + (2n+2) + (2n²+2n) + (2n³+2n²) + 
 	(2n³) + (2n³) + (n³) = 7n³ + 8n² + 11n + 6.

 Custo total do algorítimo de Floyd é: 
 	7n³ + 8n² + 11n + 6
	O(n³)
 */