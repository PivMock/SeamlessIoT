import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MinMaxScaler

# Step 1: Load data
df = pd.read_csv("mock_sensor_data.csv")
df['timestamp'] = pd.to_datetime(df['timestamp'])

# Step 2: Drop timestamp or extract features (optional)
df['hour'] = df['timestamp'].dt.hour
df['minute'] = df['timestamp'].dt.minute
df = df.drop(columns=['timestamp'])

# Step 3: Separate features and label
X = df.drop(columns=['label'])
y = df['label']

# Step 4: Normalize features
scaler = MinMaxScaler()
X_scaled = scaler.fit_transform(X)

# Step 5: Train-test split
X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.2, random_state=42)

# Save for next phase
import joblib
joblib.dump((X_train, X_test, y_train, y_test), "sensor_data_split.pkl")
print("Data preprocessed and saved to 'sensor_data_split.pkl'")